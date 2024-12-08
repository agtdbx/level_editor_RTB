MESON_CONFIG_DIR	:= build
MESON_BUILD_DIR		:= release


all: build
	ninja -C $(MESON_CONFIG_DIR)
	ninja install -C $(MESON_CONFIG_DIR) >/dev/null

build:
	meson $(MESON_CONFIG_DIR) --prefix=$$PWD/$(MESON_BUILD_DIR) --bindir="" --libdir=""

clean:
	rm -rf $(MESON_BUILD_DIR)

fclean: clean
	rm -rf $(MESON_CONFIG_DIR)

re: clean all

run: all
	cd $(MESON_BUILD_DIR) && ./RTB_editor

runval: all
	cd $(MESON_BUILD_DIR) && valgrind ./RTB_editor

.PHONY: all clean fclean re run runval
