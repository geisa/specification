###############################################################################
# Example builds and grouped example targets.
###############################################################################

# To add a new C++ example:
#   1. Add the .cpp basename to CPP_EXAMPLE_IDS
#   2. Define CPP_EXAMPLE_<name>_PROTO_DEPS := <proto1 proto2 ...>
CPP_EXAMPLE_IDS := waveform_subscribe_and_read
CPP_EXAMPLE_waveform_subscribe_and_read_PROTO_DEPS := waveform geisa-status
CPP_EXAMPLES := $(addprefix $(EXAMPLESDIR)/,$(CPP_EXAMPLE_IDS))

define DEFINE_CPP_EXAMPLE
$(EXAMPLESDIR)/$(1): examples/$(1).cpp $(foreach proto,$(CPP_EXAMPLE_$(1)_PROTO_DEPS),$(CPPDIR)/$(proto).pb.cc $(CPPDIR)/$(proto).pb.h)
	@mkdir -p $(EXAMPLESDIR)
	c++ -std=c++17 -O2 -I$(CPPDIR) $(PROTOBUF_CFLAGS) \
	  examples/$(1).cpp \
	  $(foreach proto,$(CPP_EXAMPLE_$(1)_PROTO_DEPS),$(CPPDIR)/$(proto).pb.cc) \
	  $(PROTOBUF_LIBS) -pthread \
	  -o $$@
endef

$(foreach example,$(CPP_EXAMPLE_IDS),$(eval $(call DEFINE_CPP_EXAMPLE,$(example))))

define COMPILE_NANOPB_EXAMPLE
	@if [ "$(NANOPB_RUNTIME_AVAILABLE)" != "yes" ]; then \
	  echo "NANOPB_DIR or NANOPB_RUNTIME_DIR must point to a nanopb source tree containing pb_common.c, pb_encode.c, and pb_decode.c."; \
	  exit 1; \
	fi
	cc -std=c11 -O2 \
	  -I$(NANOPBDIR) \
	  -I$(NANOPB_RUNTIME_DIR_EFFECTIVE) \
	  $(1) \
	  $(call nanopb-module-pbcs,$(2)) \
	  $(NANOPB_RUNTIME_DIR_EFFECTIVE)/pb_common.c \
	  $(NANOPB_RUNTIME_DIR_EFFECTIVE)/pb_encode.c \
	  $(NANOPB_RUNTIME_DIR_EFFECTIVE)/pb_decode.c \
	  -o $(3)
endef

define DEFINE_EMBEDDED_EXAMPLE
$(EXAMPLESDIR)/$(1)_c: examples/$(1).c examples/helpers/$(2)_example_utils.h examples/helpers/nanopb_example_utils.h $(call nanopb-module-stamps,$(3))
	@mkdir -p $(EXAMPLESDIR)
	$(call COMPILE_NANOPB_EXAMPLE,examples/$(1).c,$(3),$(EXAMPLESDIR)/$(1)_c)
endef

define DEFINE_EMBEDDED_FAMILY
EMBEDDED_EXAMPLES_$(1) := $(addprefix $(EXAMPLESDIR)/,$(addsuffix _c,$(2)))
examples-$(1): $$(EMBEDDED_EXAMPLES_$(1))
$(foreach example,$(2),$(eval $(call DEFINE_EMBEDDED_EXAMPLE,$(example),$(3),$(4))))
endef

# To add a new embedded C example family:
#   $(eval $(call DEFINE_EMBEDDED_FAMILY,<family>,<example1 example2 ...>,<helper_prefix>,<nanopb module deps>))
#   <family>       -> target name (e.g., examples-<family>)
#   <example1..>   -> .c filenames (e.g., actuator_write_response_example)
#   <helper_prefix> -> helper header stem (e.g., actuator -> actuator_example_utils.h)
#   <nanopb deps>  -> space-separated nanopb module names (e.g., status actuator)
#
$(eval $(call DEFINE_EMBEDDED_FAMILY,actuator,actuator_write_response_example actuator_read_example,actuator,status actuator))
$(eval $(call DEFINE_EMBEDDED_FAMILY,app-message,app_message_write_response_example app_message_read_example,app_message,app_message))
$(eval $(call DEFINE_EMBEDDED_FAMILY,conn-status,conn_status_write_example conn_status_read_example,conn_status,conn_status))
$(eval $(call DEFINE_EMBEDDED_FAMILY,sensor,sensor_write_response_example sensor_read_example,sensor,status sensor))
$(eval $(call DEFINE_EMBEDDED_FAMILY,discovery,discovery_write_request_example discovery_write_response_example discovery_read_example,discovery,status sensor waveform discovery))
$(eval $(call DEFINE_EMBEDDED_FAMILY,metered,metered_quantities_write_example metered_quantities_read_example,metered_quantities,metered))

examples-cpp: $(CPP_EXAMPLES)
	@echo "Built active C++ examples in $(EXAMPLESDIR) (waveform only)"

examples-c: nanopb-prereqs examples-actuator examples-app-message examples-conn-status examples-sensor examples-discovery examples-metered
	@echo "Built embedded C examples in $(EXAMPLESDIR)"

DEFAULT_EXAMPLE_TARGETS := examples-cpp
ifeq ($(NANOPB_DEFAULT_READY),yes)
DEFAULT_EXAMPLE_TARGETS += examples-c
endif

examples: $(DEFAULT_EXAMPLE_TARGETS)
ifeq ($(NANOPB_DEFAULT_READY),yes)
	@echo "Built all currently supported examples."
else
	@printf '%s\n' \
	  'Built the active C++ example set.' \
	  'Skipped embedded C examples because nanopb prerequisites are not ready.' \
	  'Recommended setup:' \
	  '  make setup-dev' \
	  '  test -d /tmp/nanopb/.git || git clone https://github.com/nanopb/nanopb /tmp/nanopb' \
	  '  make clean' \
	  '  make examples-c'
endif

demos:
	scripts/run-demos.sh

.PHONY: examples examples-cpp examples-c \
	examples-actuator examples-app-message examples-conn-status \
	examples-sensor examples-discovery examples-metered demos
