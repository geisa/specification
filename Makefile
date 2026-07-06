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

# To solve mermaid issue when building on
# RPi aarch system system
ARCH := $(shell uname -m)
MMDC_FLAGS :=
ifeq ($(ARCH),aarch64)
MMDC_FLAGS += --puppeteerConfigFile puppeteer-config.json
endif


# Put it first so that "make" without argument is like "make help".
help:
	@echo "GEISA Specification targets:"
	@echo "  clean       Clean repo"
	@echo "  all         Build all GEISA outputs ($(SPHINXTARGETS))"
	@for TT in $(SPHINXTARGETS); do printf "  %-10s  Build GEISA %s output\n" $$TT $$TT; done
	@echo
	@echo "Or build custom Sphinx target with:"
	@echo "  SPHINXTARGETS=foo make all"
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS)

.DELETE_ON_ERROR:

.PHONY: help Makefile clean all prep $(SPHINXTARGETS)

clean:
	rm -f $(IMAGEPDF)
	rm -f $(MERMAIDSVG)
	rm -f $(MERMAIDPDF)
	rm -f $(DRAWIOSVG)
	rm -f $(DRAWIOPDF)
	rm -rf $(BUILDDIR)

prep: $(MERMAIDSVG) $(IMAGEPDF) $(MERMAIDPDF) $(DRAWIOSVG) $(DRAWIOPDF)

all: $(SPHINXTARGETS)

%.svg: %.mermaid
	mmdc $(MMDC_FLAGS) -i $< -o $@

%.svg: %.drawio
	drawio --export --crop --format svg --output $@ $<

%.pdf: %.drawio
	drawio --export --crop --format pdf --output $@ $<

%.pdf: %.svg
	rsvg-convert -f=pdf -o $@ $<

$(SPHINXTARGETS): Makefile prep
	$(SHELL) -c "PATH=$(PYTHONVENV:/=/bin:)$$PATH $(SPHINXBUILD) -M $@ \"$(SOURCEDIR)\" \"$(BUILDDIR)\" $(SPHINXOPTS)"
