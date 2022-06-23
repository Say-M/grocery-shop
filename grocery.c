#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ! structures
struct product_struct
{
    int id;
    char name[50];
    float price;
    int stock;
} product;

struct invoice_struct {
    int id;
    char customer[50];
    int product;
    int quantity;
    char date[50];
} invoice;

FILE *fp;

void menu() {
    printf("\n\n========== Grocery Shop ==========\n\n");
    printf("Available Commands\n");
    printf("------------------\n");

    // ! Available commands
    printf("1: Add Product\n");
    printf("2: Display Products\n");
    printf("3: Update Product\n");
    printf("0: Exit\n");
}

void addProduct() {
    char name[20] = "products.txt";
    fp = fopen("products.txt", "a");
    printf("Enter data for product\n");
    printf("\n\n---------------------------\n");
    printf("Product ID: ");
    scanf("%d", &product.id);
    printf("Product Name: ");
    fflush(stdin); // clean input buffer
    fgets(product.name, sizeof(product.name), stdin);
    strtok(product.name, "\n"); // remove newline
    printf("Product Price: ");
    fflush(stdin);
    scanf("%f", &product.price);
    printf("Product Stock: ");
    scanf("%d", &product.stock);
    fwrite(&product, sizeof(product), 1, fp);
    fclose(fp);
    printf("\nProduct Successfully Added");
}

void showProducts(){
    int record = 0;
    fp = fopen("products.txt", "r");
    printf("===== Showing all products =====\n\n");
    while (fread(&product, sizeof(product), 1, fp) == 1) {
        record++;
        if(record == 1) printf("%-10s %-30s %-30s %s\n", "ID", "Name", "Price", "Stock");
        printf("%-10d %-30s %-30.2f %d\n", product.id, product.name, product.price, product.stock);
    }
    if(record == 0) printf("No products available ...\n");
    fclose(fp);
}
void showProductByCriteria(){
    char search[200], id[10], price[10], stock[10];
    printf("Search anything : ");
    fgets(search, sizeof(search), stdin);
    strtok(search, "\n"); // remove newline
    int record = 0;
    fp = fopen("products.txt", "r");
    printf("===== Showing all products =====\n\n");
    while (fread(&product, sizeof(product), 1, fp) == 1) {
        // ! convert int and float into string
        gcvt(product.price, 10, price);
        itoa(product.stock, stock, 10);
        itoa(product.id, id, 10);
        if(strstr(id, search) || strstr(product.name, search) || strstr(price, search) || strstr(stock, search)) {
            record++;
            if(record == 1) printf("%-10s %-30s %-30s %s\n", "ID", "Name", "Price", "Stock");
            printf("%-10d %-30s %-30.2f %d\n", product.id, product.name, product.price, product.stock);
        }
    }
    if(record == 0) printf("No products available ...\n");
    fclose(fp);
}

void updateProduct() {
    int record = 0, id;
    fp = fopen("products.txt", "r+");
    printf("===== Update A Product =====\n\n");
    printf("Enter Product ID: ");
    scanf("%d", &id);
    while (fread(&product, sizeof(product), 1, fp) == 1) {
        if(product.id == id) {
            record++;
            printf("Enter New Product Name: ");
            fflush(stdin); // clean input buffer
            fgets(product.name, sizeof(product.name), stdin);
            strtok(product.name, "\n"); // remove newline
            printf("Enter New Product Price: ");
            fflush(stdin);
            scanf("%f", &product.price);
            printf("Enter New Product Stock: ");
            scanf("%d", &product.stock);
            fseek(fp, -sizeof(product), 1);
            fwrite(&product, sizeof(product), 1, fp);
            break;
        }
    }
    if(record == 0) printf("No products available for updating ...\n");
    else printf("A product with %d id updated", id);
    fclose(fp);
}

int main()
{
    int choice = 1;
    while (choice) {
        menu();
        printf("Enter a choice: ");
        scanf("%d", &choice);
        fflush(stdin); // clean input buffer
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                char secChoice;
                printf("\n\n------------------------\n");
                printf("a. Show All Products\n");
                printf("b. Search For Products\n");
                printf("Enter a secondary choice: ");
                scanf("%c", &secChoice);
                fflush(stdin); // clean input buffer
                if(secChoice == 'a' || secChoice == 'A') showProducts();
                else if(secChoice == 'b' || secChoice == 'B') showProductByCriteria();
                else printf("Invalid Command!\n");
                break;
            case 3:
                updateProduct();
                break;
            case 0:
                break;
        }
    }
    return 0;
}