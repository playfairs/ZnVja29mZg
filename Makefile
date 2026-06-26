BUILDDIR = build
SHELL := /bin/sh
PATH := /bin:/usr/bin
RM = /bin/rm
MKDIR = /bin/mkdir
INSTALL = /usr/bin/install
CC = /usr/bin/clang
CFLAGS = -std=c2x -O2 -march=native -Wall -Wextra -Iinclude
PKG_CONFIG ?= pkg-config
SDL_CFLAGS = $(shell if command -v $(PKG_CONFIG) >/dev/null 2>&1; then $(PKG_CONFIG) --cflags sdl3; else printf -- "-I/nix/store/lvxw9x180p5bxpy3j9bxpp42hx99ql0m-sdl3-3.2.10-dev/include"; fi)
SDL_LIBS = $(shell if command -v $(PKG_CONFIG) >/dev/null 2>&1; then $(PKG_CONFIG) --libs sdl3; else printf -- "-L/nix/store/gnyijvz4vji5fa6vvg5130rhmfmz9pdv-sdl3-3.2.10-lib/lib -lSDL3"; fi)
SRCS = src/core/main.c src/core/app.c src/core/gfx.c src/core/audio.c src/core/rnd.c src/core/vec.c src/core/util_math.c src/core/sys.c src/visuals/s0.c src/visuals/s1.c src/visuals/s2.c src/visuals/s3.c src/visuals/s4.c src/visuals/s5.c src/visuals/s6.c src/visuals/s7.c src/visuals/s8.c src/visuals/s9.c src/visuals/sA.c src/visuals/sB.c src/visuals/sC.c src/visuals/sD.c src/visuals/sE.c src/visuals/sF.c
OBJS = $(SRCS:src/%.c=$(BUILDDIR)/%.o)
TARGET = $(BUILDDIR)/ZnVja29mZg
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o $@ $(OBJS) $(SDL_LIBS)
$(BUILDDIR)/%.o: src/%.c | $(BUILDDIR)
	$(MKDIR) -p $(dir $@)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@
$(BUILDDIR):
	$(MKDIR) -p $(BUILDDIR)
clean:
	$(RM) -rf $(BUILDDIR)
install: $(TARGET)
	$(INSTALL) -d $(DESTDIR)/usr/local/bin
	$(INSTALL) -m 755 $(TARGET) $(DESTDIR)/usr/local/bin/$(notdir $(TARGET))
.PHONY: all clean install
