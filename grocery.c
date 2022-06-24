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
} product[100];

// struct invoice_struct {
//     int id;
//     char customer[50];
//     int product;
//     int quantity;
//     char date[50];
// } invoice;

FILE *fp, *ft;

void menu() {
    printf("\n\n========== Grocery Shop ==========\n\n");
    printf("Available Commands\n");
    printf("------------------\n");

    // ! Available commands
    printf("1: Add Product\n");
    printf("2: Display Products\n");
    printf("3: Sort Products\n");
    printf("4: Update Product\n");
    printf("5: Delete Product\n");
    printf("0: Exit\n\n");
}

void addProduct() {
    int record = 0;
    char name[20] = "products.txt";
    fp = fopen("products.txt", "a+");
    fseek(fp, 0, SEEK_END);
    record = ftell(fp)/sizeof(product);
    printf("Enter data for product\n");
    printf("----------------------\n");
    printf("Product ID: ");
    scanf("%d", &product[record].id);
    printf("Product Name: ");
    fflush(stdin); // clean input buffer
    fgets(product[record].name, sizeof(product[record].name), stdin);
    strtok(product[record].name, "\n"); // remove newline
    printf("Product Price: ");
    fflush(stdin);
    scanf("%f", &product[record].price);
    printf("Product Stock: ");
    scanf("%d", &product[record].stock);
    fwrite(&product, sizeof(product), 1, fp);
    fclose(fp);
    printf("\nProduct Successfully Added");
}

void showProducts(){
    int record = 0, count = 0;
    fp = fopen("products.txt", "r");
    printf("\n\n**** Showing All Products ****\n\n");
    while (fread(&product, sizeof(product), 1, fp) == 1) {
        record++;
        if(record == 1) printf("%-10s %-30s %-30s %s\n", "ID", "Name", "Price", "Stock");
        printf("%-10d %-30s %-30.2f %d\n", product[count].id, product[count].name, product[count].price, product[count].stock);
        count++;
    }
    if(record == 0) printf("No products available ...\n");
    fclose(fp);
}
void showProductByCriteria(){
    char search[200], id[10], price[10], stock[10];
    printf("Search anything : ");
    fgets(search, sizeof(search), stdin);
    strtok(search, "\n"); // remove newline
    int record = 0, count = 0;
    fp = fopen("products.txt", "r");
    printf("\n\n**** Showing All Products By Criteria Match ****\n\n");
    while (fread(&product, sizeof(product), 1, fp) == 1) {
        // ! convert int and float into string
        gcvt(product[count].price, 10, price);
        itoa(product[count].stock, stock, 10);
        itoa(product[count].id, id, 10);
        if(strstr(id, search) || strstr(product[count].name, search) || strstr(price, search) || strstr(stock, search)) {
            record++;
            if(record == 1) printf("%-10s %-30s %-30s %s\n", "ID", "Name", "Price", "Stock");
            printf("%-10d %-30s %-30.2f %d\n", product[count].id, product[count].name, product[count].price, product[count].stock);
        }
        count++;
    }
    if(record == 0) printf("No products available ...\n");
    fclose(fp);
}

void sortAscProducts() {
    struct product_struct temp_p[100], temp;
    int record = 0, i, j, sortChoice;
    fp = fopen("products.txt", "r");
    printf("\n\n---- Sorting Info ----\n");
    printf("1: Sort By ID\n");
    printf("2: Sort By Name\n");
    printf("3: Sort By Price\n");
    printf("4: Sort By Stock\n");
    scanf("%d", &sortChoice);
    while (fread(&product, sizeof(product), 1, fp) == 1) {
        temp_p[record] = product[record];
        record++;
    }
    if(sortChoice == 1) {
        for(i = 0; i < record; i++)
            for(j = i + 1; j < record; j++) {
                if(temp_p[i].id > temp_p[j].id) {
                    temp = temp_p[i];
                    temp_p[i] = temp_p[j];
                    temp_p[j] = temp;
                }
            }
    } else if(sortChoice == 2) {
        for(i = 0; i < record; i++)
            for(j = i + 1; j < record; j++) {
                if(strcmp(temp_p[i].name, temp_p[j].name) > 0) {
                    temp = temp_p[i];
                    temp_p[i] = temp_p[j];
                    temp_p[j] = temp;
                }
            }
    } else if(sortChoice == 3) {
        for(i = 0; i < record; i++)
            for(j = i + 1; j < record; j++) {
                if(temp_p[i].price > temp_p[j].price) {
                    temp = temp_p[i];
                    temp_p[i] = temp_p[j];
                    temp_p[j] = temp;
                }
            }
    } else if(sortChoice == 4) {
        for(i = 0; i < record; i++)
            for(j = i + 1; j < record; j++) {
                if(temp_p[i].stock > temp_p[j].stock) {
                    temp = temp_p[i];
                    temp_p[i] = temp_p[j];
                    temp_p[j] = temp;
                }
            }
    }
    if(record == 0) return printf("No products available ...\n");
    printf("\n\n**** Showing All Products By Ascending Order ****\n\n");
    printf("%-10s %-30s %-30s %s\n", "ID", "Name", "Price", "Stock");
    for (i = 0; i < record; i++) {
        printf("%-10d %-30s %-30.2f %d\n", temp_p[i].id, temp_p[i].name, temp_p[i].price, temp_p[i].stock);
    }
    fclose(fp);
}


void sortDscProducts() {
    struct product_struct temp_p[100], temp;
    int record = 0, i, j, sortChoice;
    fp = fopen("products.txt", "r");
    printf("\n\n---- Sorting Info ----\n");
    printf("1: Sort By ID\n");
    printf("2: Sort By Name\n");
    printf("3: Sort By Price\n");
    printf("4: Sort By Stock\n");
    scanf("%d", &sortChoice);
    while (fread(&product, sizeof(product), 1, fp) == 1) {
        temp_p[record] = product[record];
        record++;
    }
    if(sortChoice == 1) {
        for(i = 0; i < record; i++)
            for(j = i + 1; j < record; j++) {
                if(temp_p[i].id < temp_p[j].id) {
                    temp = temp_p[i];
                    temp_p[i] = temp_p[j];
                    temp_p[j] = temp;
                }
            }
    } else if(sortChoice == 2) {
        for(i = 0; i < record; i++)
            for(j = i + 1; j < record; j++) {
                if(strcmp(temp_p[i].name, temp_p[j].name) < 0) {
                    temp = temp_p[i];
                    temp_p[i] = temp_p[j];
                    temp_p[j] = temp;
                }
            }
    } else if(sortChoice == 3) {
        for(i = 0; i < record; i++)
            for(j = i + 1; j < record; j++) {
                if(temp_p[i].price < temp_p[j].price) {
                    temp = temp_p[i];
                    temp_p[i] = temp_p[j];
                    temp_p[j] = temp;
                }
            }
    } else if(sortChoice == 4) {
        for(i = 0; i < record; i++)
            for(j = i + 1; j < record; j++) {
                if(temp_p[i].stock < temp_p[j].stock) {
                    temp = temp_p[i];
                    temp_p[i] = temp_p[j];
                    temp_p[j] = temp;
                }
            }
    }
    if(record == 0) return printf("No products available ...\n");
    printf("\n\n**** Showing All Products By Ascending Order ****\n\n");
    printf("%-10s %-30s %-30s %s\n", "ID", "Name", "Price", "Stock");
    for (i = 0; i < record; i++) {
        printf("%-10d %-30s %-30.2f %d\n", temp_p[i].id, temp_p[i].name, temp_p[i].price, temp_p[i].stock);
    }
    fclose(fp);
}

void updateProduct() {
    int record = 0, id, count = 0;
    fp = fopen("products.txt", "r+");
    printf("\n\n**** Update A Product ****\n\n");
    printf("Enter Product ID: ");
    scanf("%d", &id);
    while (fread(&product, sizeof(product), 1, fp) == 1) {
        if(product[count].id == id) {
            record++;
            printf("Enter New Product Name: ");
            fflush(stdin); // clean input buffer
            fgets(product[count].name, sizeof(product[count].name), stdin);
            strtok(product[count].name, "\n"); // remove newline
            printf("Enter New Product Price: ");
            fflush(stdin);
            scanf("%f", &product[count].price);
            printf("Enter New Product Stock: ");
            scanf("%d", &product[count].stock);
            fseek(fp, -sizeof(product), 1);
            fwrite(&product, sizeof(product), 1, fp);
            break;
        }
        count++;
    }
    if(record == 0) printf("No products available with the id of %d for updating ...\n", id);
    else printf("A product with %d id updated", id);
    fclose(fp);
}

void deleteProduct() {
    int record = 0, id, count = 0;
    fp = fopen("products.txt", "r+");
    ft = fopen("temp.txt", "w");
    printf("\n\n**** Delete A Product ****\n\n");
    printf("Enter Product ID: ");
    scanf("%d", &id);
    while (fread(&product, sizeof(product), 1, fp) == 1) {
        if(product[count].id == id) record++;
        else fwrite(&product, sizeof(product), 1, ft);
        count++;
    }
    fclose(fp);
    fclose(ft);
    if(record == 0) printf("No products available with the id of %d for updating ...\n", id);
    else printf("A product with %d id deleted", id);
    remove("products.txt");
    rename("temp.txt", "products.txt");
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
                char subChoice;
                printf("a. Sort By Ascending\n");
                printf("b. Sort By Descending\n");
                printf("Enter a secondary choice: ");
                scanf("%c", &subChoice);
                fflush(stdin); // clean input buffer
                if(subChoice == 'a' || subChoice == 'A') sortAscProducts();
                else if(subChoice == 'b' || subChoice == 'B') sortDscProducts();
                else printf("Invalid Command!\n");
                break;
            case 4:
                updateProduct();
                break;
            case 5:
                deleteProduct();
                break;
            case 0:
                break;
        }
    }
    return 0;
}