#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define prodMAX 100
#define maxname 50
#define FILENAME "products.txt"

void printMenu() {
    printf("\nMenu:");
    printf("\n1. Add a product");
    printf("\n2. Update a product");
    printf("\n3. Search for a product with name");
    printf("\n4. Increase quantity of a product");
    printf("\n5. Decrease quantity of a product");
    printf("\n6. List all products");
    printf("\n7. Exit\n");
    printf("Enter your choice (1-6): ");
}

struct Product {
    int id;
    char name[maxname];
    char unit[maxname];
    int quantity;
};

struct Product productData[prodMAX];
int numProducts = 0;

int main() {
    uploadData();

    int choice;
    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProduct();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                increaseQuantity();
                break;
            case 5:
                decreaseQuantity();
                break;
            case 6:
                printProducts();
                break;
            case 7:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 7);

    return 0;
}

void uploadData() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        exit(1);
    }

    while (fscanf(file, "%d,%49[^,],%49[^,],%d\n", &productData[numProducts].id, productData[numProducts].name, productData[numProducts].unit, &productData[numProducts].quantity) == 4) {
        numProducts++;
    }

    fclose(file);
}

void dataSave() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        exit(1);
    }
    int i;
    for (i = 0; i < numProducts; i++) {
        fprintf(file, "%d,%s,%s,%d\n", productData[i].id, productData[i].name, productData[i].unit, productData[i].quantity);
    }

    fclose(file);
}

void addProduct() {
    struct Product newProduct;
    printf("Enter product ID: ");
    scanf("%d", &newProduct.id);
    int i;

    
    int usedID = 0;
    for (i = 0; i < numProducts; i++) {
        if (productData[i].id == newProduct.id) {
            usedID = 1;
            printf("Error: Product ID already exists. Enter a different ID.\n");
            break;
        }
    }

    if (!usedID) {
        getchar(); 
        printf("Enter name of the product: ");
        fgets(newProduct.name, maxname, stdin);
        size_t len = strlen(newProduct.name);
        if (len > 0 && newProduct.name[len - 1] == '\n') {
            newProduct.name[len - 1] = '\0'; 
        }
        printf("Enter the unit: ");
        fgets(newProduct.unit, maxname, stdin);
        len = strlen(newProduct.unit);
        if (len > 0 && newProduct.unit[len - 1] == '\n') {
            newProduct.unit[len - 1] = '\0'; 
        }
        printf("Enter the quantity: ");
        scanf("%d", &newProduct.quantity);

        productData[numProducts++] = newProduct;
        dataSave();
        printf("Product inserted successfully.\n");
    }
}

void updateProduct() {
    int productId, MARK = -1;
    printf("Enter product number(ID) to update: ");
    scanf("%d", &productId);
    printf("product found. Which field would you like to update?\n");

    int usedID = 0;
    int i;
    for (i = 0; i < numProducts; i++) {
        if (productData[i].id == productId) {
            usedID = 1;
            break;
        }
    }

    if (!usedID) {
        printf("Error: Product ID does not exist.\n");
        return;
    }

    for (i = 0; i < numProducts; i++) {
        if (productData[i].id == productId) {
            MARK = i;
            break;
        }
    }

    if (MARK != -1) {
        int choice;
        printf("1. Name\n2. Unit\n3. Quantity\n4. ID\nEnter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter new name: ");
                getchar(); 
                fgets(productData[MARK].name, maxname, stdin);
                size_t len = strlen(productData[MARK].name);
                if (len > 0 && productData[MARK].name[len - 1] == '\n') {
                    productData[MARK].name[len - 1] = '\0'; 
                }
                break;
            case 2:
                printf("Enter new unit: ");
                getchar(); 
                fgets(productData[MARK].unit, maxname, stdin);
                len = strlen(productData[MARK].unit);
                if (len > 0 && productData[MARK].unit[len - 1] == '\n') {
                    productData[MARK].unit[len - 1] = '\0'; 
                }
                break;
            case 3:
                printf("Enter new quantity: ");
                scanf("%d", &productData[MARK].quantity);
                break;
            case 4:
                printf("Enter new ID: ");
                scanf("%d", &productData[MARK].id);
                break;
            default:
                printf("Invalid choice.\n");
        }

        dataSave();
        printf("Product updated successfully.\n");
    } else {
        printf("Product not found.\n");
    }
}

void searchProduct() {
    char searchName[maxname];
    printf("Enter name of the product: ");
    getchar(); 
    fgets(searchName, maxname, stdin);
    size_t len = strlen(searchName);
    if (len > 0 && searchName[len - 1] == '\n') {
        searchName[len - 1] = '\0';
    }

    printf("Products from %s:\n", searchName);
    int cantFOUND = 0;
    int i;
    for (i = 0; i < numProducts; i++) {
        if (strstr(productData[i].name, searchName) != NULL) {
            printf("%-5d%-20s%-15s%-10d\n", productData[i].id, productData[i].name,
			 productData[i].unit, productData[i].quantity);
            cantFOUND++;
        }
    }

    if (cantFOUND == 0) {
        printf("No matching product found.\n");
    }
}

void increaseQuantity() {
    int productId, addQuantity, MARK = -1;
    printf("Enter product number(ID) to update: ");
    scanf("%d", &productId);
    printf("Enter the increment quantity: ");
    scanf("%d", &addQuantity);
    int i;
    for (i = 0; i < numProducts; i++) {
        if (productData[i].id == productId) {
            MARK = i;
            break;
        }
    }

    if (MARK != -1) {
        productData[MARK].quantity += addQuantity;
        printf("Quantity increased successfully.\n");
        printf("New quantity of %s: %d\n", productData[MARK].name, productData[MARK].quantity); 
        dataSave(); 
    } else {
        printf("Product not found.\n");
    }
}
int changeProduct(const void *a, const void *b) {
    struct Product *Prod1 = (struct Product *)a;
    struct Product *Prod2 = (struct Product *)b;
    return Prod1->id - Prod2->id;
}
void decreaseQuantity() {
    int productId, decreaseQuantity, MARK = -1;
    printf("Enter product number(ID) to update: ");
    scanf("%d", &productId);
    printf("Enter the decrement quantity: ");
    scanf("%d", &decreaseQuantity);
    int i;
    for (i = 0; i < numProducts; i++) {
        if (productData[i].id == productId) {
            MARK = i;
            break;
        }
    }

    if (MARK != -1) {
        if (decreaseQuantity <= productData[MARK].quantity) {
            productData[MARK].quantity -= decreaseQuantity;
            printf("Quantity decreased successfully.\n");
            printf("New quantity of %s: %d\n", productData[MARK].name, productData[MARK].quantity); // Display the new quantity value
            dataSave(); // Save the update to the file
        } else {
            printf("Error: The amount to be subtracted is larger than the current amount!\n");
        }
    } else {
        printf("Product not found.\n");
    }
}

void changeQuantity() {
    int choice;
    printf("1. Increase quantity\n2. Decrease quantity\nEnter your choice (1-2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            increaseQuantity();
            break;
        case 2:
            decreaseQuantity();
            break;
        default:
            printf("Invalid choice.\n");
    }
}

void printProducts() {
    qsort(productData, numProducts, sizeof(struct Product), changeProduct);

    printf("Current products list:\n");
    printf("%-5s%-35s%-25s%-16s\n", "ID", "Name", "Unit", "Quantity");
    int i;
    for (i = 0; i < numProducts; i++) {
        printf("%-5d%-35s%-25s%-16d\n", productData[i].id, productData[i].name, productData[i].unit, productData[i].quantity);
    }
}

