# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SPHINXTARGETS ?= html latexpdf
SOURCEDIR     = source
BUILDDIR      = build

IMAGESVG      = $(wildcard $(SOURCEDIR)/images/*.svg)
IMAGEPDF      = $(patsubst %.svg,%.pdf,$(IMAGESVG))

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
	rm -rf $(BUILDDIR)

prep: $(IMAGEPDF)

all: $(SPHINXTARGETS)

%.pdf: %.svg
	rsvg-convert -f=pdf -o $@ $<

$(SPHINXTARGETS): Makefile prep
	$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS)
