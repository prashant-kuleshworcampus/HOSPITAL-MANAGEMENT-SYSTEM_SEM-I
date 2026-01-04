#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATIENT_FILE "patients.dat"
#define DOCTOR_FILE "doctors.dat"
#define BILL_FILE "bills.dat"
#define ASSIGNMENT_FILE "assignments.dat"

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[100];
} Patient;

typedef struct {
    int id;
    char name[50];
    char specialization[50];
} Doctor;

typedef struct {
    int patientID;
    int doctorID;
} Assignment;

typedef struct {
    int patientID;
    float roomCharges;
    float medicineCharges;
    float doctorFees;
    float total;
} Bill;

void addPatient() {
    Patient p;
    FILE *fp = fopen(PATIENT_FILE, "ab");
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    getchar();
    printf("Enter Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;
    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar();
    printf("Enter Gender: ");
    fgets(p.gender, sizeof(p.gender), stdin);
    p.gender[strcspn(p.gender, "\n")] = 0;
    printf("Enter Disease: ");
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

    fwrite(&p, sizeof(Patient), 1, fp);
    fclose(fp);
    printf("Patient added successfully.\n");
}

void viewPatients() {
    Patient p;
    FILE *fp = fopen(PATIENT_FILE, "rb");
    printf("\n[.....Patient List.....]\n\n");
    while (fread(&p, sizeof(Patient), 1, fp)) {
        printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\n\n",
               p.id, p.name, p.age, p.gender, p.disease);
    }
    fclose(fp);
}

void searchPatient() {
    int id;
    Patient p;
    FILE *fp = fopen(PATIENT_FILE, "rb");
    printf("Enter Patient ID to search: ");
    scanf("%d", &id);
    int found = 0;
    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == id) {
            printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\n",
                   p.id, p.name, p.age, p.gender, p.disease);
            found = 1;
            break;
        }
    }
    if (!found) printf("Patient not found.\n");
    fclose(fp);
}

void editPatient() {
    int id, found = 0;
    Patient p;
    FILE *fp = fopen(PATIENT_FILE, "rb+");
    printf("Enter Patient ID to edit: ");
    scanf("%d", &id);
    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == id) {
            printf("Editing Patient ID %d\n", id);
            getchar();
            printf("Enter new Name: ");
            fgets(p.name, sizeof(p.name), stdin);
            p.name[strcspn(p.name, "\n")] = 0;
            printf("Enter new Age: ");
            scanf("%d", &p.age);
            getchar();
            printf("Enter new Gender: ");
            fgets(p.gender, sizeof(p.gender), stdin);
            p.gender[strcspn(p.gender, "\n")] = 0;
            printf("Enter new Disease: ");
            fgets(p.disease, sizeof(p.disease), stdin);
            p.disease[strcspn(p.disease, "\n")] = 0;
            fseek(fp, -sizeof(Patient), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, fp);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (found) printf("Patient updated successfully.\n");
    else printf("Patient not found.\n");
}

void deletePatient() {
    int id, found = 0;
    Patient p;
    FILE *fp = fopen(PATIENT_FILE, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);
    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id != id) fwrite(&p, sizeof(Patient), 1, temp);
        else found = 1;
    }
    fclose(fp);
    fclose(temp);
    remove(PATIENT_FILE);
    rename("temp.dat", PATIENT_FILE);
    if (found) printf("Patient deleted successfully.\n");
    else printf("Patient not found.\n");
}

void addDoctor() {
    Doctor d;
    FILE *fp = fopen(DOCTOR_FILE, "ab");
    printf("Enter Doctor ID: ");
    scanf("%d", &d.id);
    getchar();
    printf("Enter Name: ");
    fgets(d.name, sizeof(d.name), stdin);
    d.name[strcspn(d.name, "\n")] = 0;
    printf("Enter Specialization: ");
    fgets(d.specialization, sizeof(d.specialization), stdin);
    d.specialization[strcspn(d.specialization, "\n")] = 0;
    fwrite(&d, sizeof(Doctor), 1, fp);
    fclose(fp);
    printf("Doctor added successfully.\n");
}

void viewDoctors() {
    Doctor d;
    FILE *fp = fopen(DOCTOR_FILE, "rb");
    printf("\n[....Doctor List....]\n\n");
    while (fread(&d, sizeof(Doctor), 1, fp)) {
        printf("ID: %d\nName: %s\nSpecialization: %s\n\n",
               d.id, d.name, d.specialization);
    }
    fclose(fp);
}

void editDoctor() {
    int id, found = 0;
    Doctor d;
    FILE *fp = fopen(DOCTOR_FILE, "rb+");
    printf("Enter Doctor ID to edit: ");
    scanf("%d", &id);
    while (fread(&d, sizeof(Doctor), 1, fp)) {
        if (d.id == id) {
            printf("Editing Doctor ID %d\n", id);
            getchar();
            printf("Enter new Name: ");
            fgets(d.name, sizeof(d.name), stdin);
            d.name[strcspn(d.name, "\n")] = 0;
            printf("Enter new Specialization: ");
            fgets(d.specialization, sizeof(d.specialization), stdin);
            d.specialization[strcspn(d.specialization, "\n")] = 0;
            fseek(fp, -sizeof(Doctor), SEEK_CUR);
            fwrite(&d, sizeof(Doctor), 1, fp);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (found) printf("Doctor updated successfully.\n");
    else printf("Doctor not found.\n");
}

void deleteDoctor() {
    int id, found = 0;
    Doctor d;
    FILE *fp = fopen(DOCTOR_FILE, "rb");
    FILE *temp = fopen("temp_doctor.dat", "wb");
    printf("Enter Doctor ID to delete: ");
    scanf("%d", &id);
    while (fread(&d, sizeof(Doctor), 1, fp)) {
        if (d.id != id) fwrite(&d, sizeof(Doctor), 1, temp);
        else found = 1;
    }
    fclose(fp);
    fclose(temp);
    remove(DOCTOR_FILE);
    rename("temp_doctor.dat", DOCTOR_FILE);
    if (found) printf("Doctor deleted successfully.\n");
    else printf("Doctor not found.\n");
}

void assignDoctor() {
    Assignment a;
    FILE *fp = fopen(ASSIGNMENT_FILE, "ab");
    printf("Enter Patient ID: ");
    scanf("%d", &a.patientID);
    printf("Enter Doctor ID: ");
    scanf("%d", &a.doctorID);
    fwrite(&a, sizeof(Assignment), 1, fp);
    fclose(fp);
    printf("Doctor assigned to patient successfully.\n");
}

void viewPatientDoctorRelation() {
    Assignment a;
    Doctor d;
    Patient p;
    FILE *af = fopen(ASSIGNMENT_FILE, "rb");
    while (fread(&a, sizeof(Assignment), 1, af)) {
        FILE *pf = fopen(PATIENT_FILE, "rb");
        FILE *df = fopen(DOCTOR_FILE, "rb");
        while (fread(&p, sizeof(Patient), 1, pf)) {
            if (p.id == a.patientID) break;
        }
        while (fread(&d, sizeof(Doctor), 1, df)) {
            if (d.id == a.doctorID) break;
        }
        printf("\nPatient: %s (ID: %d)\nDoctor: %s (ID: %d, Specialization: %s)\n",
               p.name, p.id, d.name, d.id, d.specialization);
        fclose(pf);
        fclose(df);
    }
    fclose(af);
}

void generateBill() {
    Bill b;
    FILE *fp = fopen(BILL_FILE, "ab");
    printf("Enter Patient ID: ");
    scanf("%d", &b.patientID);
    printf("Enter Room Charges: ");
    scanf("%f", &b.roomCharges);
    printf("Enter Medicine Charges: ");
    scanf("%f", &b.medicineCharges);
    printf("Enter Doctor Fees: ");
    scanf("%f", &b.doctorFees);
    b.total = b.roomCharges + b.medicineCharges + b.doctorFees;
    fwrite(&b, sizeof(Bill), 1, fp);
    fclose(fp);
    printf("Bill generated successfully.\n");
}

void viewBill() {
    int id, found = 0;
    Bill b;
    FILE *fp = fopen(BILL_FILE, "rb");
    printf("Enter Patient ID to view bill: ");
    scanf("%d", &id);
    while (fread(&b, sizeof(Bill), 1, fp)) {
        if (b.patientID == id) {
            printf("\nRoom Charges: %.2f\nMedicine Charges: %.2f\nDoctor Fees: %.2f\nTotal: %.2f\n",
                   b.roomCharges, b.medicineCharges, b.doctorFees, b.total);
            found = 1;
            break;
        }
    }
    if (!found) printf("Bill not found.\n");
    fclose(fp);
}

void viewPatientHistory() {
    int id, found = 0;
    Patient p;
    Doctor d;
    Assignment a;
    Bill b;
    printf("Enter Patient ID to view history: ");
    scanf("%d", &id);

    FILE *pf = fopen(PATIENT_FILE, "rb");
    while (fread(&p, sizeof(Patient), 1, pf)) {
        if (p.id == id) {
            printf("\n\n[.....Patient Information....]\nID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\n\n",
                   p.id, p.name, p.age, p.gender, p.disease);
            found = 1;
            break;
        }
    }
    fclose(pf);
    if (!found) {
        printf("Patient not found.\n");
        return;
    }

    int doctorFound = 0;
    FILE *af = fopen(ASSIGNMENT_FILE, "rb");
    while (fread(&a, sizeof(Assignment), 1, af)) {
        if (a.patientID == id) {
            FILE *df = fopen(DOCTOR_FILE, "rb");
            while (fread(&d, sizeof(Doctor), 1, df)) {
                if (d.id == a.doctorID) {
                    printf("\n\n[....Assigned Doctor....]\nID: %d\nName: %s\nSpecialization: %s\n\n",
                           d.id, d.name, d.specialization);
                    doctorFound = 1;
                    break;
                }
            }
            fclose(df);
            break;
        }
    }
    fclose(af);
    if (!doctorFound)
        printf("\nNo doctor assigned.\n");

    int billFound = 0;
    FILE *bf = fopen(BILL_FILE, "rb");
    while (fread(&b, sizeof(Bill), 1, bf)) {
        if (b.patientID == id) {
            printf("\n\n[.....Billing.....]\n\nRoom Charges: %.2f\nMedicine Charges: %.2f\nDoctor Fees: %.2f\nTotal: %.2f\n\n\n",
                   b.roomCharges, b.medicineCharges, b.doctorFees, b.total);
            billFound = 1;
            break;
        }
    }
    fclose(bf);
    if (!billFound)
        printf("\nNo billing record found.\n");
}

int main() {
    int choice;
    do {
        printf("|------------------------------------|\n");
        printf("|                KAC                 |\n");
        printf("|                                    |\n");
        printf("|     HOSPITAL MANAGEMENT SYSTEM     |\n");
        printf("|____________________________________|\n\n\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Search Patient\n");
        printf("4. Edit Patient\n");
        printf("5. Delete Patient\n");
        printf("6. Add Doctor\n");
        printf("7. View Doctors\n");
        printf("8. Edit Doctor\n");
        printf("9. Delete Doctor\n");
        printf("10. Assign Doctor to Patient\n");
        printf("11. View Patient-Doctor Relationship\n");
        printf("12. Generate Bill\n");
        printf("13. View Bill\n");
        printf("14. View Patient History\n");
        printf("15. Exit\n\n\n\n\n");
        
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: editPatient(); break;
            case 5: deletePatient(); break;
            case 6: addDoctor(); break;
            case 7: viewDoctors(); break;
            case 8: editDoctor(); break;
            case 9: deleteDoctor(); break;
            case 10: assignDoctor(); break;
            case 11: viewPatientDoctorRelation(); break;
            case 12: generateBill(); break;
            case 13: viewBill(); break;
            case 14: viewPatientHistory(); break;
            case 15: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 15);
    return 0;
}

