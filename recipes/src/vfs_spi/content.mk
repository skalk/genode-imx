MIRROR_FROM_REP_DIR  += lib/mk/vfs_spi-imx8.mk src/lib/vfs/spi

content: $(MIRROR_FROM_REP_DIR)

$(MIRROR_FROM_REP_DIR):
	$(mirror_from_rep_dir)

