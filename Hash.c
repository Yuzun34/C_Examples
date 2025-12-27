#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define EMPTY -1

// Hash tablosu yapısı
typedef struct {
    int table[TABLE_SIZE];
} HashTable;

// Hash tablosunu başlat
void initHashTable(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = EMPTY;
    }
}

// Hash fonksiyonu: h(key) = key mod 10
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Hash tablosunu yazdır
void printHashTable(HashTable *ht) {
    printf("\n--- HASH TABLOSU ---\n");
    printf("Indeks | Deger\n");
    printf("-------|-------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("  [%d]  |  ", i);
        if (ht->table[i] == EMPTY) {
            printf("-\n");
        } else {
            printf("%d\n", ht->table[i]);
        }
    }
    printf("--------------------\n");
}

// Lineer probing ile eleman ekleme
int insertValue(HashTable *ht, int value) {
    int index = hashFunction(value);
    int originalIndex = index;
    int probeCount = 0;
    
    printf("\n--- EKLEME İŞLEMİ ---\n");
    printf("Eklenen değer: %d\n", value);
    printf("Hash değeri: %d mod %d = %d\n", value, TABLE_SIZE, index);
    
    // Boş yer bul
    while (ht->table[index] != EMPTY) {
        printf("Çakışma! İndeks [%d] dolu (değer: %d)\n", index, ht->table[index]);
        probeCount++;
        
        if (probeCount >= TABLE_SIZE) {
            printf("HATA: Hash tablosu dolu! Eleman eklenemedi.\n");
            return 0;
        }
        
        index = (index + 1) % TABLE_SIZE;
        printf("Yeni indeks deneniyor: [%d]\n", index);
    }
    
    // Değeri yerleştir
    ht->table[index] = value;
    
    if (probeCount > 0) {
        printf("\nSonuç: %d değeri %d adımda [%d] indeksine yerleştirildi.\n", 
               value, probeCount, index);
        printf("(İlk hash değeri: [%d], Son konum: [%d])\n", 
               originalIndex, index);
    } else {
        printf("\nSonuç: %d değeri direkt olarak [%d] indeksine yerleştirildi.\n", 
               value, index);
    }
    
    return 1;
}

// Değer arama
int searchValue(HashTable *ht, int value) {
    int index = hashFunction(value);
    int originalIndex = index;
    int probeCount = 0;
    
    while (ht->table[index] != EMPTY) {
        if (ht->table[index] == value) {
            printf("%d değeri [%d] indeksinde bulundu.\n", value, index);
            return index;
        }
        
        probeCount++;
        if (probeCount >= TABLE_SIZE) {
            break;
        }
        
        index = (index + 1) % TABLE_SIZE;
        
        // Başladığımız yere döndük
        if (index == originalIndex) {
            break;
        }
    }
    
    printf("%d değeri tabloda bulunamadı.\n", value);
    return -1;
}

// Menü göster
void showMenu() {
    printf("\n--- MENU ---\n");
    printf("1. Eleman Ekle\n");
    printf("2. Eleman Ara\n");
    printf("3. Tabloyu Göster\n");
    printf("4. Tabloyu Sıfırla\n");
    printf("5. Çıkış\n");
    printf("Seçim: ");
}

int main() {
    HashTable ht;
    int choice, value;
    
    initHashTable(&ht);
    
    printf("\nLINEER PROBING HASH TABLOSU\n");
    printf("Tablo Boyutu: 10\n");
    printf("Hash Fonksiyonu: h(key) = key mod 10\n");
    
    while (1) {
        showMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Gecersiz giris! Lutfen bir sayi girin.\n");
            while (getchar() != '\n'); // Buffer temizle
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("\nEklenecek tamsayi: ");
                if (scanf("%d", &value) != 1) {
                    printf("Gecersiz giris!\n");
                    while (getchar() != '\n');
                    break;
                }
                insertValue(&ht, value);
                break;
                
            case 2:
                printf("\nAranacak deger: ");
                if (scanf("%d", &value) != 1) {
                    printf("Gecersiz giris!\n");
                    while (getchar() != '\n');
                    break;
                }
                searchValue(&ht, value);
                break;
                
            case 3:
                printHashTable(&ht);
                break;
                
            case 4:
                initHashTable(&ht);
                printf("\nHash tablosu sifirlandi.\n");
                break;
                
            case 5:
                printf("\nProgram sonlandiriliyor...\n");
                return 0;
                
            default:
                printf("\nGecersiz secim! Lutfen 1-5 arasi bir deger girin.\n");
        }
        
        printf("\nDevam etmek icin Enter'a basin...");
        while (getchar() != '\n');
        getchar();
    }
    
    return 0;
}