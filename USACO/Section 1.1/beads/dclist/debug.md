__GI___libc_malloc (bytes=140737488345920) at malloc.c:2876
2876	malloc.c: No such file or directory.
(gdb) bt
#0  __GI___libc_malloc (bytes=140737488345920) at malloc.c:2876
#1  0x0000000000400a77 in dclist_ins_next (list=0x7fffffffdcf0, element=0x0, 
    data=0x7fffffffdcc0) at dclist.c:40
#2  0x000000000040095d in main () at test_dclist.c:46
