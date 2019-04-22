# -*-Makefile-*-

OBJDIRS		+= $(KERN_OBJDIR)/vmm/MPTCow

KERN_SRCFILES	+= $(KERN_DIR)/vmm/MPTCow/MPTCow.c



$(KERN_OBJDIR)/vmm/MPTCow/%.o: $(KERN_DIR)/vmm/MPTCow/%.c
	@echo + $(COMP_NAME)[KERN/vmm/MPTCow] $<
	@mkdir -p $(@D)
	$(V)$(CCOMP) $(CCOMP_KERN_CFLAGS) -c -o $@ $<

$(KERN_OBJDIR)/vmm/MPTCow/%.o: $(KERN_DIR)/vmm/MPTCow/%.S
	@echo + as[KERN/vmm/MPTCow] $<
	@mkdir -p $(@D)
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<
