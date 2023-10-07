# PWNVOYAGE / GAME / PWN-VOYAGE_L1

Here we have a prompt, necessary to cross the bridge.

```

caigoshinobi@freyja:~$ ./PWN-VOYAGE_L1

======================================================

 ██▓    ▓█████ ██▒   █▓▓█████  ██▓           ██▓
▓██▒    ▓█   ▀▓██░   █▒▓█   ▀ ▓██▒          ▓██▒
▒██░    ▒███   ▓██  █▒░▒███   ▒██░          ▒██▒
▒██░    ▒▓█  ▄  ▒██ █░░▒▓█  ▄ ▒██░          ░██░
░██████▒░▒████▒  ▒▀█░  ░▒████▒░██████▒      ░██░
░ ▒░▓  ░░░ ▒░ ░  ░ ▐░  ░░ ▒░ ░░ ▒░▓  ░      ░▓
░ ░ ▒  ░ ░ ░  ░  ░ ░░   ░ ░  ░░ ░ ▒  ░       ▒
  ░ ░      ░       ░░     ░     ░ ░          ▒
====░======░========░=====░=======░==========░========
                    ░
You stride through the very entrance of the cemetery, a
weathered wooden bridge standing as the only barrier to
the hill of the Vault beyond. The air thickens with an
eerie mist, enveloping your senses. Amidst this arcane
obscurity, you discern a malevolent presence of demonic
runes strewn across the bridge's path like sinister
breadcrumbs.

======================================================

-$> Cross the bridge:

```

Inserting the wrong string results in the death of Knight.

```

-$> Cross the bridge: aaa

-$> Place your foot upon a skull-shaped rune. In a burst
    of brilliance, it detonates, casting forth a blinding
    radiance that hurls your form into a plummet from the
    bridge's edge, descending into the unfathomable depths
    of the abyss.

-$> Yeah bro. You are dead.

```
Again, the binary is not stripped:

```

caigoshinobi@freyja:~$ file PWN-VOYAGE_L1
PWN-VOYAGE_L1: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=9f92a18eb236758041852b2bee76db1874cbcb00, for GNU/Linux 3.2.0, not stripped

```

So, we start analyzing it with dogbolt.org.


```

int __fastcall main(int argc, const char **argv, const char **envp)
{
  int v4; // [rsp+0h] [rbp-20h]
  int i; // [rsp+4h] [rbp-1Ch]
  char s[12]; // [rsp+Ch] [rbp-14h] BYREF
  unsigned __int64 v7; // [rsp+18h] [rbp-8h]

  v7 = __readfsqword(0x28u);
  banner();
  v4 = -1;
  putchar(10);
  printf("-$> Cross the bridge: ");
  fgets(s, 12, _bss_start);
  putchar(10);
  s[strcspn(s, "\n")] = 0;
  if ( strlen(s) != 11 || s[1] != 95 || s[3] != 95 || s[6] != 95 || s[0] != 85 )
    return death();
  for ( i = 0; i <= 11; ++i )
  {
    if ( s[i + 2] == 82 && s[i] == 72 && s[i + 1] == 51 && s[i + 3] == 79 )
    {
      v4 = i;
      break;
    }
  }
  if ( v4 == -1 || s[5] != 89 || s[4] != 77 || s[2] != 82 )
    return death();
  puts("-$> Bridge crossed. You have reached the hill of the Vault!");
  putchar(10);
  bridge_crossing(s);
  return 0;
}

```

Let's break down the conditions for rearranging the letters in the string:

- The length of the string must be 11 characters.
- The first character of the string (`s[0]`) must be 'U'.
- The characters at positions 1, 3, and 6 (`s[1]`, `s[3]`, and `s[6]`) must be '_'.

Next, there's a `for` loop that iterates through the string `s` from position 0 to position 11.

Within the loop, the code checks the following conditions for each character:

- The character at the current position (`s[i]`) must be 'H'.
- The character at the next position (`s[i + 1]`) must be '3'.
- The character at the position after that (`s[i + 2]`) must be 'R'.
- The character at the position after that (`s[i + 3]`) must be 'O'.

If these conditions are met for any iteration of the loop, the value of `i` is assigned to `v4`, and the loop breaks.

If `v4` is not -1, it indicates that the conditions were met. Continue to verify the following conditions:

- The character at position 2 (`s[2]`) must be 'R'.
- The character at position 4 (`s[4]`) must be 'M'.
- The character at position 5 (`s[5]`) must be 'Y'.

We finally obtain the string: **U_R_MY_H3RO**

```

-$> Cross the bridge: U_R_MY_H3RO

-$> Bridge crossed. You have reached the hill of the Vault!

-$> Flag: NTRLGC{TH1SH1LLSM3LLSL1K3V1CT0RY}

```


