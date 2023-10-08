# PWNVOYAGE / GAME / PWN-VOYAGE_BOSS

Finally, the boss level. Let's see what we have ahead.

```

caigoshinobi@freyja:~$ file PWN-VOYAGE_BOSS
PWN-VOYAGE_BOSS: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=514772e909aefa197dc12e498dc41c89fa0a5028, for GNU/Linux 3.2.0, stripped

```

If we run the level, we'll face the wraith Grimshade, and it doesn't seem like an equal fight.

```

caigoshinobi@freyja:~$ ./PWN-VOYAGE_BOSS

==========================================================================

 ▄▄▄▄    ▒█████    ██████   ██████      █████▒██▓  ▄████  ██░ ██ ▄▄▄█████▓
▓█████▄ ▒██▒  ██▒▒██    ▒ ▒██    ▒    ▓██   ▒▓██▒ ██▒ ▀█▒▓██░ ██▒▓  ██▒ ▓▒
▒██▒ ▄██▒██░  ██▒░ ▓██▄   ░ ▓██▄      ▒████ ░▒██▒▒██░▄▄▄░▒██▀▀██░▒ ▓██░ ▒░
▒██░█▀  ▒██   ██░  ▒   ██▒  ▒   ██▒   ░▓█▒  ░░██░░▓█  ██▓░▓█ ░██ ░ ▓██▓ ░
░▓█  ▀█▓░ ████▓▒░▒██████▒▒▒██████▒▒   ░▒█░   ░██░░▒▓███▀▒░▓█▒░██▓  ▒██▒ ░
░▒▓███▀▒░ ▒░▒░▒░ ▒ ▒▓▒ ▒ ░▒ ▒▓▒ ▒ ░    ▒ ░   ░▓   ░▒   ▒  ▒ ░░▒░▒  ▒ ░░
▒░▒   ░   ░ ▒ ▒░ ░ ░▒  ░ ░░ ░▒  ░ ░    ░      ▒ ░  ░   ░  ▒ ░▒░ ░    ░
 ░    ░ ░ ░ ░ ▒  ░  ░  ░  ░  ░  ░      ░ ░    ▒ ░░ ░   ░  ░  ░░ ░  ░
 ░          ░ ░        ░        ░             ░        ░  ░  ░  ░
      ░
Finally, the tomb of Grimshade hath been unsealed! The Vault is shrouded
in an ominous mist. The Wraith hovers through the chamber, its gaze fixed
upon you, while its legendary blade sways with an eerie rhythm. For a
brief moment, the two lock eyes, each assessing the other's essence. At
last, the grand clash commences, a spectacle of power and fate intertwined.

==========================================================================

-$> Defeat Grimshade!

|------------------------
| KNIGHT        HP:  50
| GRIMSHADE     HP:  255
|------------------------

Press a key to continue...

-$> You deal 5 damage to Grimshade!
-$> Grimshade inflicts 9 damage on you!

```
Let's try to help our knight by starting to analyze the binary with ghidra.
We come to know that we not only have to defeat Grimshade but also bring his HP down to exactly 0.

```

undefined8 main(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  time_t tVar4;
  uint local_24;
  uint local_20;
  
  FUN_00101ce8();
  FUN_0010212d();
  tVar4 = time((time_t *)0x0);
  srand((uint)tVar4);
  local_24 = 0x32;
  local_20 = 0xff;
  puts("-$> Defeat Grimshade!");
  while ((0 < (int)local_24 && (local_20 != 0))) {
    putchar(10);
    puts("|------------------------");
    printf("| KNIGHT        HP:  %d  \n",(ulong)local_24);
    printf("| GRIMSHADE     HP:  %d  \n",(ulong)local_20);
    puts("|------------------------");
    uVar1 = FUN_001020e5(5,0xf);
    uVar2 = FUN_001020e5(5,0xf);
    putchar(10);
    puts("Press a key to continue...");
    getchar();
    printf("-$> You deal %d damage to Grimshade!\n",(ulong)uVar1);
    local_20 = local_20 - uVar1;
    printf("-$> Grimshade inflicts %d damage on you!\n",(ulong)uVar2);
    local_24 = local_24 - uVar2;
  }
  if (local_20 == 0) {
    uVar3 = FUN_001017ff();
    puts(
        "\n-$> A skilled knight possesses, alongside sheer strength, a healthy dose of cunning.\n    You choose not to succumb to the immense power of the Wraith. With a skillful\n    sword swing, you cut the rope that holds a heavy chandelier attached to the crypt\'s\n    ceiling. Grimshade is impaled and trapped by the mass of iron, allowing you to finish\n    him off with two final strikes. Finally, you grasp the Sword of Heroes, a long-sought\n    and greatly desired weapon. A blade that, furthermore, is essential for the Main Adventure\n    that awaits you! \n"
        );
    FUN_00101841("E2F8FEE0EBEFD7F89CF3EE9FF3EF9CE29B9DE2F99FE88D84E198F5EE9F85D1",uVar3);
  }
  else {
    FUN_0010210f();
  }
  return 0;
}

```

There are several ways to solve the challenge. In this case, I will show you how to manipulate the scores with gdb.

```
pwndbg> start
pwndbg> ni 
```

`ni` stands for `next instruction`. We continue to run untile until we'll find the first prompt. Then `CTRL+C` and `ni` again until this point:

```
pwndbg> ni
 [...]
──────────────────────────────────────────────────[ DISASM / x86-64 / set emulate on ]────────────────────────────────────────────────────
   0x5555555561cc    mov    eax, dword ptr [rbp - 0x18]
   0x5555555561cf    mov    esi, eax
   0x5555555561d1    lea    rax, [rip + 0x1bf7]
   0x5555555561d8    mov    rdi, rax
   0x5555555561db    mov    eax, 0
 ► 0x5555555561e0    call   printf@plt                <printf@plt>
        format: 0x555555557dcf ◂— '| GRIMSHADE     HP:  %d  \n'
        vararg: 0xf9

   0x5555555561e5    lea    rax, [rip + 0x1bae]
   0x5555555561ec    mov    rdi, rax
   0x5555555561ef    call   puts@plt                <puts@plt>
 [...]
 
```

We know that Grimshade now have 0xf9 HP (249 HP). Again `ni` until we find this point. 

```
───────────────────────────────────────────────────[ DISASM / x86-64 / set emulate on ]────────────────────────────────────────────────────
   0x5555555561e5    lea    rax, [rip + 0x1bae]
   0x5555555561ec    mov    rdi, rax
   0x5555555561ef    call   puts@plt                <puts@plt>

   0x5555555561f4    mov    esi, 0xf
   0x5555555561f9    mov    edi, 5
 ► 0x5555555561fe    call   0x5555555560e5                <0x5555555560e5>

   0x555555556203    mov    dword ptr [rbp - 0x14], eax
   0x555555556206    mov    esi, 0xf
   0x55555555620b    mov    edi, 5
   0x555555556210    call   0x5555555560e5                <0x5555555560e5>

   0x555555556215    mov    dword ptr [rbp - 0x10], eax
─────────────────────────────────────────────────────────────────[ STACK ]─────────────────────────────────────────────────────────────────
00:0000│ rsp 0x7fffffffe6c0 ◂— 0x27ffffea49
01:0008│     0x7fffffffe6c8 ◂— 0x6000000f9
02:0010│     0x7fffffffe6d0 ◂— 0xb /* '\x0b' */
03:0018│     0x7fffffffe6d8 —▸ 0x555555555360 ◂— endbr64
04:0020│ rbp 0x7fffffffe6e0 ◂— 0x1
05:0028│     0x7fffffffe6e8 —▸ 0x7ffff796dd90 (__libc_start_call_main+128) ◂— mov edi, eax
06:0030│     0x7fffffffe6f0 ◂— 0x0
07:0038│     0x7fffffffe6f8 —▸ 0x555555556147 ◂— endbr64
───────────────────────────────────────────────────────────────[ BACKTRACE ]───────────────────────────────────────────────────────────────
 ► 0   0x5555555561fe
   1   0x7ffff796dd90 __libc_start_call_main+128
   2   0x7ffff796de40 __libc_start_main+128
   3   0x555555555385
───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
pwndbg> info registers
rax            0x1a                26
rbx            0x0                 0
rcx            0x7ffff7a58a77      140737348209271
rdx            0x1                 1
rsi            0xf                 15
rdi            0x5                 5

```

As you can see from the registers, 0x5555555560e5 is the random function that determines how much damage to deal, ranging from 5 (rdi) to 15 (rsi).
Let's change both to 0xf9 and continue:

```

pwndbg> set $rsi=0xf9
pwndbg> set $rdi=0xf9
pwndbg> continue
Continuing.

Press a key to continue...

-$> You deal 249 damage to Grimshade!
-$> Grimshade inflicts 5 damage on you!

-$> A skilled knight possesses, alongside sheer strength, a healthy dose of cunning.
    You choose not to succumb to the immense power of the Wraith. With a skillful
    sword swing, you cut the rope that holds a heavy chandelier attached to the crypt's
    ceiling. Grimshade is impaled and trapped by the mass of iron, allowing you to finish
    him off with two final strikes. Finally, you grasp the Sword of Heroes, a long-sought
    and greatly desired weapon. A blade that, furthermore, is essential for the Main Adventure
    that awaits you!

-$> Flag: NTRLGC{T0_B3_C0N71NU3D!(M4YB3)}

```