#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//gcc PWN-VOYAGE_PROLOGUE.c -o PWN-VOYAGE_PROLOGUE

void demonic_things(const unsigned char *input, const char *key, unsigned char *output, size_t length) {
    size_t key_len = strlen(key);
	for (size_t i = 0; i < length; i++) {
        output[i] = input[i] ^ key[i % key_len];
    }
	
}

void signpost(const char *path) {
    const char *lock = "041D031E341D1B150010097A1A121E7C1A1B1624";
    unsigned char decoded[128];
    int len = strlen(lock) / 2;
	
    for (int i = 0; i < len; i++) {
        sscanf(&lock[i * 2], "%02hhX", &decoded[i]);
    }
    
	unsigned char decrypted[128];
	memset(decrypted, 0, sizeof(decrypted));
    demonic_things(decoded, path, decrypted, len);
    printf("-$> So, you've got: %s\n", decrypted);
    printf("\n");
}

void banner() {
	printf("\n"
	   "=====================================================================\n"
	   "                                                                     \n"
	   " ██▓███   ██▀███   ▒█████   ██▓     ▒█████    ▄████  █    ██ ▓█████  \n"
	   "▓██░  ██▒▓██ ▒ ██▒▒██▒  ██▒▓██▒    ▒██▒  ██▒ ██▒ ▀█▒ ██  ▓██▒▓█   ▀  \n"
	   "▓██░ ██▓▒▓██ ░▄█ ▒▒██░  ██▒▒██░    ▒██░  ██▒▒██░▄▄▄░▓██  ▒██░▒███    \n"
	   "▒██▄█▓▒ ▒▒██▀▀█▄  ▒██   ██░▒██░    ▒██   ██░░▓█  ██▓▓▓█  ░██░▒▓█  ▄  \n"
	   "▒██▒ ░  ░░██▓ ▒██▒░ ████▓▒░░██████▒░ ████▓▒░░▒▓███▀▒▒▒█████▓ ░▒████▒ \n"
	   "▒▓▒░ ░  ░░ ▒▓ ░▒▓░░ ▒░▒░▒░ ░ ▒░▓  ░░ ▒░▒░▒░  ░▒   ▒ ░▒▓▒ ▒ ▒ ░░ ▒░ ░ \n"
	   "░▒ ░       ░▒ ░ ▒░  ░ ▒ ▒░ ░ ░ ▒  ░  ░ ▒ ▒░   ░   ░ ░░▒░ ░ ░  ░ ░  ░ \n"
	   "░░         ░░   ░ ░ ░ ░ ▒    ░ ░   ░ ░ ░ ▒  ░ ░   ░  ░░░ ░ ░    ░    \n"
	   "            ░         ░ ░      ░  ░    ░ ░        ░    ░        ░  ░ \n"
	   "                                                                     \n"
       "You have long forsaken the well-trodden paths of farmers and herders,\n"
	   "yet the road to the Vault remains distant. The route you are pursuing\n"
	   "appears abandoned for decades, overgrown with brambles. At last, you \n" 
	   "come across a few signposts, haphazardly arranged upon an ancient    \n"
	   "dead tree. Some seem fallen, making it challenging to discern the    \n" 
	   "direction to take.                                                   \n"
	   "                                                                     \n"
	   "=====================================================================\n"
	   "\n");
}

int labels() {
	printf("-$> Signpost:\n\n"
           "    II   YOUNG Shadows Inn\n"
           "    III  Mystic Tor TO Darkness\n"
           "    IV   Everglow DIE Woods\n"
           "    V    Eldermist BRO Hold\n"
		   "\n");
	return 1;
}

int main() {
    char path[100];
	banner();
	labels();
    printf("-$> Choose the right path to proceed: ");
    fgets(path, sizeof(path), stdin);
	printf("\n");
    if (strlen(path) > 0 && path[strlen(path) - 1] == '\n') {
        path[strlen(path) - 1] = '\0';
    }
    signpost(path);
    return 0;
}

int I_signpost_TOO_SpineChilling_Manor() {
	return 0;
}