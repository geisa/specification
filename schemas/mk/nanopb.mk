###############################################################################
# Nanopb code generation and grouped embedded-C prerequisites.
###############################################################################

NANOPB_RUNTIME_AVAILABLE := $(if $(and $(NANOPB_RUNTIME_DIR_EFFECTIVE),$(wildcard $(NANOPB_RUNTIME_DIR_EFFECTIVE)/pb_common.c),$(wildcard $(NANOPB_RUNTIME_DIR_EFFECTIVE)/pb_encode.c),$(wildcard $(NANOPB_RUNTIME_DIR_EFFECTIVE)/pb_decode.c)),yes,no)
NANOPB_PLUGIN_AVAILABLE := $(shell if command -v "$(NANOPB_GENERATOR)" >/dev/null 2>&1; then printf yes; else printf no; fi)
NANOPB_GENERATOR_AVAILABLE := $(if $(strip $(NANOPB_GENERATOR_MODULE)),yes,$(NANOPB_PLUGIN_AVAILABLE))
NANOPB_DEFAULT_READY := $(if $(filter yes,$(NANOPB_RUNTIME_AVAILABLE)),$(if $(filter yes,$(NANOPB_GENERATOR_AVAILABLE)),yes,no),no)

define NANOPB_GENERATE
	@mkdir -p $(NANOPBDIR)
	@if [ -n "$(strip $(NANOPB_GENERATOR_MODULE))" ]; then \
	  module_status=0; \
	  $(PYTHON) -m $(NANOPB_GENERATOR_MODULE) -D $(NANOPBDIR) -I $(NANOPB_OPTIONS_DIR) --protoc-opt=-I. $(foreach opt,$(PROTOC_OPTS),--protoc-opt=$(opt)) $(1) || module_status=$$?; \
	  if { [ $$module_status -ne 0 ] || [ ! -f "$(word 1,$(2))" ]; } && [ -n "$(NANOPB_VENV_SITE_PACKAGES)" ]; then \
	    PYTHONPATH="$(NANOPB_VENV_SITE_PACKAGES)$${PYTHONPATH:+:$$PYTHONPATH}" $(NANOPB_HOST_PYTHON) -m $(NANOPB_GENERATOR_MODULE) -D $(NANOPBDIR) -I $(NANOPB_OPTIONS_DIR) --protoc-opt=-I. $(foreach opt,$(PROTOC_OPTS),--protoc-opt=$(opt)) $(1) || exit $$?; \
	  elif [ $$module_status -ne 0 ]; then \
	    exit $$module_status; \
	  fi; \
	else \
	  plugin="$(NANOPB_GENERATOR)"; \
	  if [ -x "$$plugin" ]; then \
	    plugin="$$(cd "$$(dirname "$$plugin")" && pwd)/$$(basename "$$plugin")"; \
	  elif command -v "$$plugin" >/dev/null 2>&1; then \
	    plugin="$$(command -v "$$plugin")"; \
	  else \
	    echo "Missing nanopb generator: $(NANOPB_GENERATOR)"; \
	    echo "Set NANOPB_GENERATOR to protoc-gen-nanopb or an explicit generator path."; \
	    echo "Alternatively, set NANOPB_GENERATOR_MODULE=nanopb.generator.nanopb_generator when the nanopb Python package is importable."; \
	    exit 1; \
	  fi; \
	  if head -1 "$$plugin" | grep -q '^#!'; then \
	    plugin_wrapper="$(NANOPBDIR)/protoc-gen-nanopb-wrapper.sh"; \
	    printf '%s\n' '#!/bin/sh' "PYTHONPATH=\"$(NANOPB_VENV_SITE_PACKAGES)\$${PYTHONPATH:+:\$$PYTHONPATH}\" exec $(NANOPB_HOST_PYTHON) \"$$plugin\" \"\$$@\"" > "$$plugin_wrapper"; \
	    chmod +x "$$plugin_wrapper"; \
	    plugin="$$plugin_wrapper"; \
	  fi; \
	  $(PROTOC) $(PROTOC_FLAGS) -I. --plugin=protoc-gen-nanopb="$$plugin" --nanopb_out=$(NANOPBDIR) --nanopb_opt=-I$(NANOPB_OPTIONS_DIR) $(1) || exit $$?; \
	fi; \
	for output in $(2); do \
	  if [ ! -f "$$output" ]; then \
	    echo "nanopb generation did not produce expected file: $$output"; \
	    exit 1; \
	  fi; \
	done
endef

nanopb-module-stamps = $(foreach module,$(1),$(NANOPB_$(module)_STAMP))
nanopb-module-pbcs = $(foreach module,$(1),$(NANOPB_$(module)_PBC))

# To add a new nanopb module:
#   1. Add the module name to NANOPB_MODULES
#   2. Define NANOPB_<module>_STEM (proto stem without .proto)
#   3. Define NANOPB_<module>_OPTIONS (path to sidecar .options file, may be empty)
#   4. Define NANOPB_<module>_DEPS (space-separated module names this proto depends on)
# The DEFINE_NANOPB_MODULE macro below auto-generates stamp rules and variables.
NANOPB_MODULES := status actuator app_message conn_status sensor waveform discovery metered

NANOPB_status_STEM := geisa-status
NANOPB_status_OPTIONS := $(NANOPB_OPTIONS_DIR)/geisa-status.options
NANOPB_status_DEPS :=

NANOPB_actuator_STEM := actuator
NANOPB_actuator_OPTIONS := $(NANOPB_OPTIONS_DIR)/actuator.options
NANOPB_actuator_DEPS := status

NANOPB_app_message_STEM := app-message
NANOPB_app_message_OPTIONS := $(NANOPB_OPTIONS_DIR)/app-message.options
NANOPB_app_message_DEPS :=

NANOPB_conn_status_STEM := conn-status
NANOPB_conn_status_OPTIONS := $(NANOPB_OPTIONS_DIR)/conn-status.options
NANOPB_conn_status_DEPS :=

NANOPB_sensor_STEM := sensor
NANOPB_sensor_OPTIONS := $(NANOPB_OPTIONS_DIR)/sensor.options
NANOPB_sensor_DEPS := status

NANOPB_waveform_STEM := waveform
NANOPB_waveform_OPTIONS :=  # no sidecar options file currently needed
NANOPB_waveform_DEPS := status

NANOPB_discovery_STEM := discovery
NANOPB_discovery_OPTIONS := $(NANOPB_OPTIONS_DIR)/discovery.options
NANOPB_discovery_DEPS := status sensor waveform

NANOPB_metered_STEM := metered_quantities
NANOPB_metered_OPTIONS := $(NANOPB_OPTIONS_DIR)/metered_quantities.options
NANOPB_metered_DEPS :=

define DEFINE_NANOPB_MODULE
NANOPB_$(1)_PROTO := $$(NANOPB_$(1)_STEM).proto
NANOPB_$(1)_PBC := $$(NANOPBDIR)/$$(NANOPB_$(1)_STEM).pb.c
NANOPB_$(1)_PBH := $$(NANOPBDIR)/$$(NANOPB_$(1)_STEM).pb.h
NANOPB_$(1)_GEN := $$(NANOPB_$(1)_PBC) $$(NANOPB_$(1)_PBH)
NANOPB_$(1)_STAMP := $$(NANOPBDIR)/.$(1).nanopb.stamp

$$(NANOPB_$(1)_STAMP): $$(NANOPB_$(1)_PROTO) $$(NANOPB_$(1)_OPTIONS) $$(call nanopb-module-stamps,$$(NANOPB_$(1)_DEPS))
	$$(call NANOPB_GENERATE,$$(NANOPB_$(1)_PROTO),$$(NANOPB_$(1)_GEN))
	@touch $$@
endef

$(foreach module,$(NANOPB_MODULES),$(eval $(call DEFINE_NANOPB_MODULE,$(module))))

nanopb-prereqs:
	@if [ "$(NANOPB_RUNTIME_AVAILABLE)" != "yes" ]; then \
	  echo "Missing nanopb runtime sources."; \
	  echo "Set NANOPB_DIR or NANOPB_RUNTIME_DIR to a nanopb source tree containing pb_common.c, pb_encode.c, and pb_decode.c."; \
	  exit 1; \
	fi
	@if [ "$(NANOPB_GENERATOR_AVAILABLE)" != "yes" ]; then \
	  echo "Missing nanopb generator."; \
	  echo "Use the repo venv via 'make setup-dev', or set NANOPB_GENERATOR to protoc-gen-nanopb, or set NANOPB_GENERATOR_MODULE=nanopb.generator.nanopb_generator."; \
	  exit 1; \
	fi

actuator-c: $(call nanopb-module-stamps,status actuator)
app-message-c: $(call nanopb-module-stamps,app_message)
conn-status-c: $(call nanopb-module-stamps,conn_status)
sensor-c: $(call nanopb-module-stamps,status sensor)
discovery-c: $(call nanopb-module-stamps,status sensor waveform discovery)
metered-c: $(call nanopb-module-stamps,metered)

.PHONY: nanopb-prereqs actuator-c app-message-c conn-status-c sensor-c discovery-c metered-c
