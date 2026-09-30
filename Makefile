# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SPHINXTARGETS ?= html latexpdf
SOURCEDIR     = source
BUILDDIR      = build

# detect and use the python venv if present
ifneq ("$(wildcard $(PWD)/venv/bin/python)", "")
PYTHONVENV	= $(PWD)/venv/
else
PYTHONVENV	=
endif

# GEISA is supporting mermaid and drawio diagrams as part of the spec, but
# these diagrams are treated as independent source files to be built.  RST
# files should reference the image.

MERMAID 		= $(shell find $(SOURCEDIR) -name '*.mermaid')
MERMAIDSVG		= $(patsubst %.mermaid, %.svg,$(MERMAID))
MERMAIDPDF		= $(patsubst %.mermaid, %.pdf,$(MERMAID))

DRAWIO        	= $(shell find $(SOURCEDIR) -name '*.drawio')
DRAWIOSVG     	= $(patsubst %.drawio, %.svg,$(DRAWIO))
DRAWIOPDF     	= $(patsubst %.drawio, %.pdf,$(DRAWIO))

IMAGESVG      	= $(wildcard $(SOURCEDIR)/images/*.svg)
IMAGEPDF      	= $(patsubst %.svg,%.pdf,$(IMAGESVG))
LICENSEGEN     = .github/scripts/generate-license-rst.py
LICENSERST     = $(SOURCEDIR)/license.generated.rst.inc

JSON			= $(shell find $(SOURCEDIR) -name '*.json' ! -name package-lock.json)
JSONRST			= $(patsubst %.json, %.rst, $(JSON))

# To solve mermaid issue when building on
# RPi aarch system system
ARCH := $(shell uname -m)
MMDC_FLAGS :=
ifeq ($(ARCH),aarch64)
MMDC_FLAGS += --puppeteerConfigFile puppeteer-config.json
endif

# determine if rsvg-convert supports "pdfX.X" in format
RSVG_PDF_VER = 1.5
$(shell rsvg-convert -f=pdf$(RSVG_PDF_VER) </dev/null 2>&1 |grep -q USAGE)
ifneq ($(.SHELLSTATUS),0)
RSVG_FORMAT = pdf$(RSVG_PDF_VER)
else
RSVG_FORMAT = pdf
endif

# Put it first so that "make" without argument is like "make help".
help:
	@echo "GEISA Specification targets:"
	@echo "  clean       Clean repo"
	@echo "  cleanlatex  Clean LaTex build directory"
	@echo "  all         Build all GEISA outputs ($(SPHINXTARGETS))"
	@for TT in $(SPHINXTARGETS); do printf "  %-10s  Build GEISA %s output\n" $$TT $$TT; done
	@echo
	@echo "Or build custom Sphinx target with:"
	@echo "  SPHINXTARGETS=foo make all"
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS)

.DELETE_ON_ERROR:

.PHONY: help Makefile clean all prep license-rst license-check schemas schemas-all schemas-clean schemas-lint lint setup-dev $(SPHINXTARGETS)

clean:
	rm -f $(IMAGEPDF)
	rm -f $(MERMAIDSVG)
	rm -f $(MERMAIDPDF)
	rm -f $(DRAWIOSVG)
	rm -f $(DRAWIOPDF)
	rm -f $(LICENSERST)
	rm -f $(JSONRST)
	rm -rf $(BUILDDIR)

cleanlatex:
	rm -r $(BUILDDIR)/latex

prep: $(MERMAIDSVG) $(IMAGEPDF) $(MERMAIDPDF) $(DRAWIOSVG) $(DRAWIOPDF) $(JSONRST)

all: $(SPHINXTARGETS)

schemas:
	$(MAKE) -C schemas

schemas-all:
	$(MAKE) -C schemas all

schemas-clean:
	$(MAKE) -C schemas clean

schemas-lint:
	cd schemas && npm run lint

lint:
	npm run lint:md
	$(MAKE) schemas-lint

setup-dev:
	python3 -m venv venv
	venv/bin/python -m pip install --upgrade pip
	venv/bin/python -m pip install GitPython sphinx sphinxcontrib-svg2pdfconverter linuxdoc
	npm ci
	$(MAKE) -C schemas setup-dev
	npm --prefix schemas ci

license-rst: $(LICENSERST)

license-check: $(LICENSERST)
	PATH="$(PYTHONVENV:/=/bin:)$$PATH" python3 $(LICENSEGEN) --check

$(LICENSERST): LICENSE.md $(LICENSEGEN)
	PATH="$(PYTHONVENV:/=/bin:)$$PATH" python3 $(LICENSEGEN)

%.svg: %.mermaid
	mmdc $(MMDC_FLAGS) -i $< -o $@

%.svg: %.drawio
	drawio --export --crop --format svg --output $@ $<

%.pdf: %.drawio
	drawio --export --crop --format pdf --output $@ $<

%.pdf: %.svg
	rsvg-convert -f=$(RSVG_FORMAT) -o $@ $<

%.rst: %.json
	echo ".. code-block:: json\n  :linenos:\n" > $@
	cat $< | sed 's/^/  /' >> $@

$(SPHINXTARGETS): Makefile prep $(LICENSERST)
	PATH="$(PYTHONVENV:/=/bin:)$$PATH" $(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)/$@" $(SPHINXOPTS)
