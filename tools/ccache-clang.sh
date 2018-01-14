#!/bin/sh
if type -p ccache >/dev/null 2>&1; then
	export CCACHE_MAXSIZE=8G
  	export CCACHE_CPP2=true
  	export CCACHE_HARDLINK=true
  	export CCACHE_SLOPPINESS=file_macro,time_macros,include_file_mtime,include_file_ctime,file_stat_matches

  	exec ccache "${DEVELOPER_DIR}/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang" "$@"
else
  	exec "${DEVELOPER_DIR}/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang" "$@"
fi