#include <stdio.h>
#include <string.h>

// gcc PWN-VOYAGE_L1.c -o PWN-VOYAGE_L1

int death() {	
	printf("-$> Place your foot upon a skull-shaped rune. In a burst\n"
	       "    of brilliance, it detonates, casting forth a blinding\n"
	       "    radiance that hurls your form into a plummet from the\n"
	       "    bridge's edge, descending into the unfathomable depths\n" 
	       "    of the abyss.\n"
	       "\n"
	       "-$> Yeah bro. You are dead.\n" 
	       "\n");	
	return 1;
}

void demonic_things(const unsigned char *input, const char *key, unsigned char *output, size_t length) {
    size_t key_len = strlen(key);
	for (size_t i = 0; i < length; i++) {
        output[i] = input[i] ^ key[i % key_len];
    }
	
}

void bridge_crossing(const char *pick) {
    const char *lock = "1B0B00130A1A241C7B631C1D6E1E131E146C047F0103641461097C1A0B78610B32";
    unsigned char decoded[128];
    int len = strlen(lock) / 2;
	
    for (int i = 0; i < len; i++) {
        sscanf(&lock[i * 2], "%02hhX", &decoded[i]);
    }
    
	unsigned char decrypted[128];
	memset(decrypted, 0, sizeof(decrypted));
    demonic_things(decoded, pick, decrypted, len);
	printf("-$> After a few hours...\n"
	   "    you've obtained the right path from the old man!\n"
	   "\n");
    printf("-$> Flag: %s\n", decrypted);
    printf("\n");
}

void banner(){
	printf("\n"
	       "====================================================== \n"
		   "                                                       \n"
           " ██▓    ▓█████ ██▒   █▓▓█████  ██▓           ██▓       \n"
           "▓██▒    ▓█   ▀▓██░   █▒▓█   ▀ ▓██▒          ▓██▒       \n"
           "▒██░    ▒███   ▓██  █▒░▒███   ▒██░          ▒██▒       \n"
           "▒██░    ▒▓█  ▄  ▒██ █░░▒▓█  ▄ ▒██░          ░██░       \n"
           "░██████▒░▒████▒  ▒▀█░  ░▒████▒░██████▒      ░██░       \n"
           "░ ▒░▓  ░░░ ▒░ ░  ░ ▐░  ░░ ▒░ ░░ ▒░▓  ░      ░▓         \n"
           "░ ░ ▒  ░ ░ ░  ░  ░ ░░   ░ ░  ░░ ░ ▒  ░       ▒         \n"
           "  ░ ░      ░       ░░     ░     ░ ░          ▒         \n"
           "====░======░========░=====░=======░==========░======== \n"
           "                    ░                                  \n"
	       "You stride through the very entrance of the cemetery, a \n" 
	       "weathered wooden bridge standing as the only barrier to \n" 
	       "the hill of the Vault beyond. The air thickens with an  \n"
	       "eerie mist, enveloping your senses. Amidst this arcane  \n"
	       "obscurity, you discern a malevolent presence of demonic \n"
	       "runes strewn across the bridge's path like sinister     \n"
	       "breadcrumbs.                                            \n"
	       "                                                        \n"
	       "======================================================  \n");
}

int main() {
	
	banner();
	char safepath[12];
	int tiles = -1;
	char last_jump[] = "YMR";
	printf("\n");
    printf("-$> Cross the bridge: ");
    fgets(safepath, sizeof(safepath), stdin);
	printf("\n");
    safepath[strcspn(safepath, "\n")] = '\0';
	
    if (strlen(safepath) != 11) {
		return death();
    }
    
	if (safepath[1] != 0x5F || safepath[3] != 0x5F || safepath[6] != 0x5F) {
        return death();
    }
    
	if (safepath[0] != 0x55) {
        return death();
    }
	
	for (int i = 0; i < 12; i++) {
		if (safepath[i + 2] == '\x52' && safepath[i] == '\x48' && safepath[i + 1] == '\x33' && safepath[i + 3] == '\x4F') {
			tiles = i;
			break;
		}
	}
	
	if (tiles == -1) {
		return death();
	}
	
	if (safepath[5] != last_jump[0] || safepath[4] != last_jump[1] || safepath[2] != last_jump[2]) {
        return death();
	}
    
	printf("-$> Bridge crossed. You have reached the hill of the Vault!\n");
	printf("\n");
    bridge_crossing(safepath);
	return 0;
}