###############################################################################
# Protobuf descriptor and language-generation targets.
###############################################################################

BINPBS := $(patsubst %.proto,$(BINPBDIR)/%.binpb,$(PROTOS))
C_SRCS := $(patsubst %.proto,$(CDIR)/%.pb-c.c,$(PROTOS))
C_HDRS := $(patsubst %.proto,$(CDIR)/%.pb-c.h,$(PROTOS))
CPP_SRCS := $(patsubst %.proto,$(CPPDIR)/%.pb.cc,$(PROTOS))
CPP_HDRS := $(patsubst %.proto,$(CPPDIR)/%.pb.h,$(PROTOS))
JAVA_STAMP := $(JAVADIR)/.java_generated
PYTHON_STAMP := $(PYTHONDIR)/.python_generated

proto-descriptors: $(BINPBS)

# Legacy protobuf-c generation remains available as a best-effort path for
# standalone use, but it is not part of `make langs`.
# c is phony (below) because this is an explicit generator target — we always
# want regeneration even if the output files exist on disk.
c: $(C_SRCS) $(C_HDRS)

cpp: $(CPP_SRCS) $(CPP_HDRS)
java: $(JAVA_STAMP)
python: $(PYTHON_STAMP)

# Supported language/binding generation only. No example binaries here.
langs: cpp java python

$(BINPBDIR)/%.binpb: %.proto
	@mkdir -p $(@D)
	$(PROTOC) $(PROTOC_FLAGS) -I. -o $@ $<

$(CDIR)/%.pb-c.c $(CDIR)/%.pb-c.h: %.proto
	@mkdir -p $(CDIR)
	$(PROTOC) $(PROTOC_FLAGS) --c_out=$(CDIR) $<

$(CPPDIR)/%.pb.cc $(CPPDIR)/%.pb.h: %.proto
	@mkdir -p $(CPPDIR)
	$(PROTOC) $(PROTOC_FLAGS) --cpp_out=$(CPPDIR) $<

$(JAVA_STAMP): $(PROTOS)
	@mkdir -p $(JAVADIR)
	$(PROTOC) $(PROTOC_FLAGS) --java_out=$(JAVADIR) $(PROTOS)
	@touch $@

$(PYTHON_STAMP): $(PROTOS)
	@mkdir -p $(PYTHONDIR)
	$(PROTOC) $(PROTOC_FLAGS) --python_out=$(PYTHONDIR) $(PROTOS)
	@touch $@

.PHONY: proto-descriptors c cpp java python langs
# c is declared phony above because it is an explicit generator target.
