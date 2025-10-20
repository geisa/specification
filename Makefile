# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SPHINXTARGETS ?= html latexpdf
SOURCEDIR     = source
BUILDDIR      = build

# GEISA is supporting mermaid as part of the spec, but mermaid diagrams
# are treated as independent source files to be built.  RST files should
# reference the image.

MERMAID 			= $(shell find $(SOURCEDIR) -name '*.mermaid')
MERMAIDSVG		= $(patsubst %.mermaid, %.svg,$(MERMAID))
MERMAIDPDF		= $(patsubst %.mermaid, %.pdf,$(MERMAID))

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
	rm -f $(MERMAIDSVG)
	rm -f $(MERMAIDPDF)
	rm -rf $(BUILDDIR)

prep: $(MERMAIDSVG) $(IMAGEPDF) $(MERMAIDPDF)

all: $(SPHINXTARGETS)

%.svg: %.mermaid
	mmdc -i $< -o $@

%.pdf: %.svg
	rsvg-convert -f=pdf -o $@ $<

$(SPHINXTARGETS): Makefile prep
	$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS)
