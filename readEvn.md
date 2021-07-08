gdb install:
https://dev.to/jasonelwood/setup-gdb-on-macos-in-2020-489k
https://zhuanlan.zhihu.com/p/68398728

gdb command for debug fork:
set follow-fork-mode child
or enter it into the debug console(Ctrl+Shift+Y) in this form:
-exec set follow-fork-mode child