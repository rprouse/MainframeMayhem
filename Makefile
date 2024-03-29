#
# A Makefile that compiles all .c and .s files in "src" and "res"
# subdirectories and places the output in a "obj" subdirectory
#

# I install all of my Game Boy development tools in one root.
TOOLS_ROOT = $(HOMEDRIVE)$(HOMEPATH)/OneDrive/bin/Emulators/

# If you move this project you can change the directory
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
GBDK_HOME = $(TOOLS_ROOT)gbdk/

LCC = $(GBDK_HOME)bin/lcc
GBM2C = $(ZGB_HOME)tools/gbm2c/gbm2c
GBR2C = $(ZGB_HOME)tools/gbr2c/gbr2c
GBR2PNG = $(ZGB_HOME)tools/gbr2png/gbr2png

# Run using the bgb64.exe emulator in the path
GBEMU = $(TOOLS_ROOT)bgb/bgb64

# You can set flags for LCC here
# For example, you can uncomment the line below to turn on debug output
# LCCFLAGS = -debug
LCCFLAGS = -Wa-l -Wl-m -Wl-j
CFLAGS = -Wf-Iinclude -Wf-Ires -Wf-MMD

# You can set the name of the .gb ROM file here
PROJECTNAME = mainframe-mayhem

SRCDIR      = src
OBJDIR      = obj
RESDIR      = res
BINS	      = $(OBJDIR)/$(PROJECTNAME).gbc
CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES  = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))
OBJS        = $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)

all:	prepare $(BINS) run

# Compile .c files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(eval BAFLAG = $(shell echo "$<" | sed -n 's/.*\.ba\([0-9]\+\).*/\-Wf-ba\1/p'))
	$(LCC) $(LCCFLAGS) $(CFLAGS) $(BAFLAG) -c -o $@ $<

# Compile .c files in "res/" to .o object files
$(OBJDIR)/%.o:	$(RESDIR)/%.c
	$(LCC) $(LCCFLAGS) $(CFLAGS) -c -o $@ $<

# Compile .s assembly files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.s
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# If needed, compile .c files in "src/" to .s assembly files
# (not required if .c is compiled directly to .o)
$(OBJDIR)/%.s:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) $(CFLAGS) -S -o $@ $<

# Link the compiled object files into a .gbc ROM file
$(BINS):	$(OBJS)
	$(LCC) $(LCCFLAGS) -Wm-yC -Wm-yoA -Wm-ya4 -Wm-yt0x1B -o $(BINS) $(OBJS)

run:	$(BINS)
	$(GBEMU) --rom $(BINS)

prepare:
	mkdir -p $(OBJDIR)

clean:
#	rm -f  *.gb *.ihx *.cdb *.adb *.noi *.map
	rm -f  $(OBJDIR)/*.*
