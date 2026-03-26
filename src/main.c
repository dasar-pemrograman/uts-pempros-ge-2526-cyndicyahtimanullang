#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 100
#define MAX_LOGS 1000 

enum LogType {CMD_RECEIVE, CMD_SHIP, CMD_RESTOCK};

typedef struct {
    char id[20];
    char nama[50];
    int quantity;
    double price;
} Item;

typedef struct {
    int log_id;
    enum LogType type;
    int qty;
    char item_id[20];
} AuditLog; 

int main() {
    Item *inventory = (Item*)malloc(MAX_ITEMS * sizeof(Item));
    AuditLog *logs = (AuditLog*)malloc(MAX_LOGS * sizepf(logs));

    if (inventory == NULL || logs == NULL) {
        printf ("Gagal mengalokasikan memori!\n");
        return 1;
    }

    int itemCount = 0;
    int logCount = 0;
    int globalLogId = 1;
    char line[256];

    while (1) {
        printf("Masukkan perintah: ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        line[strcspn(line, "\r\n")] = 0;

        if (strcspn(line, "---") == 0) {
            break;
        }
        
        char *cmd = strtok(line, "#");
        if (cmd == NULL) continue;

        if (strcmp(cmd, "receive") == 0){
            char *id = strtok(NULL, "#");
            char *name = strtok(NULL, "#");
            char *qtyStr = strtok(NULL, "#");
            char *priceStr = strtok(NULL, "#");

            if (id && name && qtyStr && priceStr) {
                strcpy(inventory[itemCount].id, id);
                strcpy(inventory[itemCount].nama, name);
                inventory[itemCount].quantity = atoi(qtyStr);
                inventory[itemCount].price = atof(priceStr);

                logs[logCount].log_id = globalLogId;
                logs[logCount].type = CMD_RECEIVE;
                logs[logCount].qty = inventory[itemCount].quantity;
                strcpy(logs[logCount].item_id, id);

                globalLogId++;
                logCount++;
                itemCount++;

                printf("[SUKSES] Barang %s berhasil didaftarkan.\n", name);
            } else {
                printf("[ERROR] Format receive salah!\n");
            }

        }

        else if (strcmp(cmd, "ship") == 0 || strcmp(cmd, "restock") == 0) {
             char *typeCmd = cmd;
             char *id = strtok(NULL, "#");
             char *qtyStr = strtok(NULL, "#");

            if (!id || !qtyStr) {
                 printf("[ERROR] Format perintah salah!\n");
                 continue;
        }

        int qty = atoi(qtyStr);

        int idx = -1;
        for (int i = 0; i < itemCount; i++) {
            if (strcmp(inventory[i].id, id) == 0) {
                idx = i;
                break;
            }
        }

        if (idx != -1 && qty > 0) {
            if (strcmp(typeCmd, "ship") == 0){
                if (inventory[idx].quantity >= qty) {
                    inventory[idx].quantity -= qty;

                    logs[logCount].log_id = globalLogId++;
                    logs[logCount].type = CMD_SHIP;
                    logs[logCount].qty = qty;
                    strcpy(logs[logCount].item_id, id);
                    logCount++;

                    printf("[SUKSES] Pengiriman %d unit %s berhasil.\n", qty, inventory[idx].nama);

                }

                else {
                    printf("[GAGAL] Stok %s tidak cukup! (Sisa: %d)\n", inventory[idx].nama, inventory[idx].quantity);
                }
            } else if (strcmp(typeCmd, "restock")== 0) {
                inventory[idx].quantity += qty;

                logs[logCount].log_id = globalLogId++;
                logs[logCount].type = CMD_RESTOCK;
                logs[logCount].qty = qty;
                strcpy(logs[logCount].item_id, id);
                logCount++;

                printf("[SUKSES] Restock %d unit %s berhasil.\n", qty, inventory[idx].nama);
            }
        } else {
            if (idx == -1) printf("[GAGAL] Jumlah harus lebih besar dari 0.\n");

        }
    }

    else if (strcmp(cmd, "report") == 0) {
        printf ("\n---Laporan Inventori---\n");
        for (int i = 0; i < itemCount; i++) {
            printf("%s|%s|%d|%.1f\n", inventory[i].id, inventory[i].nama, inventory[i].quantity, inventory[i].price);

        }
        printf("-----------\n");
    }

    else if (strcmp(cmd, "audit") == 0) {
        char *id = strtok(NULL, "#");

        if (!id) {
            printf("[ERROR] Format Audit Salah!\n");
            continue;
        }

        int found = 0;
        for (int i = 0; i < itemCount; i++) {
            if (strcmp(inventory[i].id, id) == 0) {
                found = 1;

            }
        }

    }

    return 0;
}






{
    /* data */
};
;

int main() {
    char input[256];

    while (fgets(input, sizeof(input), stdin)) {
        if (strncmp(input, "---", 3) == 0) {
            break;
        }

        // TODO: implement logic
    }

    return 0;
}