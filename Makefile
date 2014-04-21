# Copyright (c) 2014, eJim Lee (lyjforpublic@gmail.com)
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the eJim Lee nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL eJim Lee BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

TARGET ?= test
CXX ?= g++
CXXFLAGS ?= -g -Werror
LINKFLAGS ?=
INCLUDES ?=
BUILD_DIR ?= build

SRCS = $(wildcard *.cpp) $(wildcard varobject/*.cpp)
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS = $(patsubst %.cpp,$(BUILD_DIR)/%.d,$(SRCS))

$(TARGET): $(OBJS)
	@echo [LD] $@
	@$(CXX) $^ -o $@ $(LINKFLAGS)

ifeq ($(strip $(MAKECMDGOALS)),)
sinclude $(DEPS)
else
ifneq ($(strip $(MAKECMDGOALS)),$(filter $(MAKECMDGOALS),clean distclean))
sinclude $(DEPS)
endif
endif

$(BUILD_DIR)/%.o: %.cpp
	@echo [CXX] $@
	@$(CXX) $< -o $@ -c $(CXXFLAGS) $(INCLUDES)

$(BUILD_DIR)/%.d: %.cpp
	@echo [DEP] $<
	@$(shell if [ ! -d $(shell dirname "$@") ]; then mkdir -p $(shell dirname "$@"); fi)
	@$(CXX) $< -MM $(CXXFLAGS) $(INCLUDES) | sed -e 's#\(.*\.o\)#$(BUILD_DIR)/\1#g' > $@

distclean: clean
	rm -rf $(TARGET)
	rm -rf $(BUILD_DIR)

clean:
	rm -rf $(OBJS) $(DEPS)

.PHONY: clean distclean
