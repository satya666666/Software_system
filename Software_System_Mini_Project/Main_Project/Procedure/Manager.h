void manager(int connFD);
int loginManager(int connFD, int mngID, char *password);
void changeStatus(int connFD);
void assignLoanApplication(int connFD);
void readFeedBack(int connFD);
int changeMNGPassword(int connFD, int mngID);

char readBuffer[4096], writeBuffer[4096];   

void manager(int connFD)
{
    struct Employee manager;
    int mngID, response = 0;
    char password[20];
    char newPassword[20];
    int choice;

label1:
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "\nEnter Manager ID: ");
    write(connFD, writeBuffer, sizeof(writeBuffer));

    bzero(readBuffer, sizeof(readBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
    mngID = atoi(readBuffer);

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter password: ");
    write(connFD, writeBuffer, sizeof(writeBuffer));

    bzero(readBuffer, sizeof(readBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(password, readBuffer);

    if(loginManager(connFD, mngID, password))
    {
        bzero(writeBuffer, sizeof(writeBuffer));
        bzero(readBuffer, sizeof(readBuffer));
        printf("Manager whose ID: %d logged In\n", mngID);
        strcpy(writeBuffer, "\nLogin Successfully^");
        write(connFD, writeBuffer, sizeof(writeBuffer));
        read(connFD, readBuffer, sizeof(readBuffer));

        while(1)
        {
            bzero(writeBuffer, sizeof(writeBuffer));
            strcpy(writeBuffer, MNGMENU);
            write(connFD, writeBuffer, sizeof(writeBuffer));

            bzero(readBuffer, sizeof(readBuffer));
            read(connFD, readBuffer, sizeof(readBuffer));
            choice = atoi(readBuffer);

            printf("Manager entered: %d\n", choice);
            switch(choice)
            {
                case 1:
                    // Activate/Deactivate Customer Accounts
                    changeStatus(connFD);
                    break;
                case 2:
                    // Assign Loan Application Processes to Employees
                    assignLoanApplication(connFD);
                    break;
                case 3:
                    // Review Customer Feedback
                    readFeedBack(connFD);
                    break;
                case 4:
                    // Change Password
                    response = changeMNGPassword(connFD, mngID);
                    if(!response)
                    {
                        bzero(writeBuffer, sizeof(writeBuffer));
                        strcpy(writeBuffer, "Unable to change password\n^");
                        write(connFD, writeBuffer, sizeof(writeBuffer));
                        read(connFD, readBuffer, sizeof(readBuffer));
                    }   
                    else
                    {
                        bzero(writeBuffer, sizeof(writeBuffer));
                        bzero(readBuffer, sizeof(readBuffer));
                        strcpy(writeBuffer,"Password changed successfully\nLogin with new password...\n^");
                        write(connFD, writeBuffer, sizeof(writeBuffer));
                        read(connFD, readBuffer, sizeof(readBuffer));
                    }                                
                    goto label1;
                case 5:
                    // Logout
                    printf("Manager Logged out!\n");
                    logout(connFD, mngID);
                    return ;
                case 6:
                    // Exit
                    printf("Manager exited\n");
                    exitClient(connFD, mngID);
                    return;
                default:
                    printf("Invalid choice\n");
            }
        }
    }
    else
    {
        bzero(writeBuffer, sizeof(writeBuffer));
        bzero(readBuffer, sizeof(readBuffer));
        strcpy(writeBuffer, "\nInvalid ID or Password^");
        write(connFD, writeBuffer, sizeof(writeBuffer));
        read(connFD, readBuffer, sizeof(readBuffer));
        goto label1;
    }
}

// Login Manager 
int loginManager(int connFD, int mngID, char *password)
{
    struct Employee mng;
    int file = open(EMPPATH, O_RDWR | O_CREAT, 0644);

    if (file == -1) {
        printf("Error opening file!\n");
        return 0;
    }

    sema = initializeSemaphore(mngID);

    setupSignalHandlers();

    if (sem_trywait(sema) == -1) {
        if (errno == EAGAIN) {
            printf("Manager %d is already logged in!\n", mngID);
        } else {
            perror("sem_trywait failed");
        }
        close(file);
        return 0;
    }

    lseek(file, 0, SEEK_SET);
    while(read(file, &mng, sizeof(mng)) != 0)
    {
        if (mng.empID == mngID && strcmp(mng.password, crypt(password, HASHKEY)) == 0 && mng.role == 0) {
            close(file);
            return 1;
        }
    }

    // sem_post(sema);

    snprintf(semName, 50, "/sem_%d", mngID);

    sem_t *sema = sem_open(semName, 0);
    if (sema != SEM_FAILED) {
        sem_post(sema);
        sem_close(sema); 
        sem_unlink(semName);    
    }


    close(file);
    return 0;
}

// Activate/Deactivate Customer Accounts 
void changeStatus(int connFD)
{
    int file = open(CUSPATH, O_CREAT | O_RDWR, 0644);
    struct Customer cs;

    int accNo, choice;

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter Account Number: ");
    write(connFD, writeBuffer, sizeof(writeBuffer));

    bzero(readBuffer, sizeof(readBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
    accNo = atoi(readBuffer);

    while(read(file, &cs, sizeof(cs)) != 0)
    {
        if(cs.accountNumber == accNo)
        {
            bzero(writeBuffer, sizeof(writeBuffer));
            strcpy(writeBuffer, "Enter 1 to Deactivate\nEnter 2 to activate\nEnter your choice: ");
            write(connFD, writeBuffer, sizeof(writeBuffer));

            bzero(readBuffer, sizeof(readBuffer));
            read(connFD, readBuffer, sizeof(readBuffer));
            choice = atoi(readBuffer);

            if(choice == 1)
            {
                lseek(file,-sizeof(struct Customer), SEEK_CUR);
                cs.activeStatus = 0;
                write(file, &cs, sizeof(cs));
                close(file);

                printf("Manager activated customer %d\n", accNo);

                bzero(readBuffer, sizeof(readBuffer));
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "Status Changed Successfully^");
                write(connFD, writeBuffer, sizeof(writeBuffer));
                read(connFD, readBuffer, sizeof(readBuffer));
                return ;
            }
            else if(choice == 2)
            {
                lseek(file, -sizeof(struct Customer), SEEK_CUR);
                cs.activeStatus = 1;
                write(file, &cs, sizeof(cs));
                close(file);

                printf("Manager deactivated customer %d\n", accNo);

                bzero(readBuffer, sizeof(readBuffer));
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "Status Changed Successfully^");
                write(connFD, writeBuffer, sizeof(writeBuffer));
                read(connFD, readBuffer, sizeof(readBuffer));
                return ;
            }
        }
    }
    close(file);
    bzero(readBuffer, sizeof(readBuffer));
    bzero(writeBuffer, sizeof(writeBuffer));
    printf("Manager entered invalid account number: %d\n", accNo);
    strcpy(writeBuffer, "Invalid account number^");
    write(connFD, writeBuffer, sizeof(writeBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
    return ;
}

//  Read Feedback 
void readFeedBack(int connFD)
{
    struct FeedBack fb;
    char tempBuffer[4096];

    int file = open(FEEDPATH, O_RDONLY);
    if(file == -1)
    {
        printf("Error in opening file\n");
    }

    bzero(tempBuffer, sizeof(tempBuffer));
    while(read(file, &fb, sizeof(fb)) != 0)
    {
        strcat(tempBuffer, fb.feedback);
        strcat(tempBuffer, "\n");
    }
    strcat(tempBuffer, "^");
    printf("Manager reading customers feedback\n");
    bzero(writeBuffer, sizeof(writeBuffer));
    bzero(readBuffer, sizeof(readBuffer));
    strcpy(writeBuffer, tempBuffer);
    write(connFD, writeBuffer, sizeof(writeBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
}

// Assign Loan Application Processes to Employees 
void assignLoanApplication(int connFD)
{
    struct LoanDetails ld;
    int file = open(LOANPATH, O_CREAT | O_RDWR, 0644);
    if(file == -1)
    {
        printf("Error in opening file\n");
        return ;
    }

    // Printing Unassigned loan application
    while(read(file, &ld, sizeof(ld)) != 0)
    {
        if(ld.empID == -1)
        {
            bzero(readBuffer, sizeof(readBuffer));
            bzero(writeBuffer, sizeof(writeBuffer));
            sprintf(writeBuffer, "Loan ID: %d\nAccount Number: %d\nLoan Amount: %d^", ld.loanID, ld.accountNumber, ld.loanAmount);
            write(connFD, writeBuffer, sizeof(writeBuffer));
            read(connFD, readBuffer, sizeof(readBuffer));
        }
    }
    lseek(file, 0, SEEK_SET);

    // Locking
    int lID, eID;

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter Loan ID: ");
    write(connFD, writeBuffer, sizeof(writeBuffer));
    
    bzero(readBuffer, sizeof(readBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
    lID = atoi(readBuffer);

    int srcOffset = -1, sourceFound = 0;
    while (read(file, &ld, sizeof(ld)) != 0)
    {
        if(ld.loanID == lID)
        {
            srcOffset = lseek(file, -sizeof(struct LoanDetails), SEEK_CUR);
            sourceFound = 1;
        }
        if(sourceFound)
            break;
    }
    if(srcOffset == -1)
    {
        bzero(writeBuffer, sizeof(writeBuffer));
        bzero(readBuffer, sizeof(readBuffer));
        sprintf(writeBuffer, "Invalid loan ID^");
        write(connFD, writeBuffer, sizeof(writeBuffer));
        read(connFD, readBuffer, sizeof(readBuffer));
        return;
    }
    
    struct flock fl1 = {F_WRLCK, SEEK_SET, srcOffset, sizeof(struct LoanDetails), getpid()};
    int result = fcntl(file, F_SETLK, &fl1);

    if(result != -1)
    {

        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Enter Employee ID: ");
        write(connFD, writeBuffer, sizeof(writeBuffer));

        bzero(readBuffer, sizeof(readBuffer));
        read(connFD, readBuffer, sizeof(readBuffer));
        eID = atoi(readBuffer);

        ld.empID = eID;
        ld.status = 1; // Pending
        printf("Manager assigned employee %d loan application\n", eID);
        write(file, &ld, sizeof(ld));

        fl1.l_type = F_UNLCK;
        fl1.l_whence = SEEK_SET;
        fl1.l_start = srcOffset;
        fl1.l_len = sizeof(struct LoanDetails);
        fl1.l_pid = getpid();

        fcntl(file, F_UNLCK, &fl1);
    }
    else
    {
        bzero(writeBuffer, sizeof(writeBuffer));
        bzero(readBuffer, sizeof(readBuffer));
        sprintf(writeBuffer, "Employee already assigned for given %d loan ID^", lID);
        write(connFD, writeBuffer, sizeof(writeBuffer));
        read(connFD, readBuffer, sizeof(readBuffer));
    }
    close(file);
    
    bzero(readBuffer, sizeof(readBuffer));
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "^");
    write(connFD, writeBuffer, sizeof(writeBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
}

//  Change Password 
int changeMNGPassword(int connFD, int mngID)
{
    char newPassword[20];

    struct Employee m;
    int file = open(EMPPATH, O_CREAT | O_RDWR, 0644);
    
    lseek(file, 0, SEEK_SET);

    int srcOffset = -1, sourceFound = 0;

    while (read(file, &m, sizeof(m)) != 0)
    {
        if(m.empID == mngID)
        {
            srcOffset = lseek(file, -sizeof(struct Employee), SEEK_CUR);
            sourceFound = 1;
        }
        if(sourceFound)
            break;
    }

    struct flock fl1 = {F_WRLCK, SEEK_SET, srcOffset, sizeof(struct Employee), getpid()};
    fcntl(file, F_SETLKW, &fl1);

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter password: ");
    write(connFD, writeBuffer, sizeof(writeBuffer));
    
    bzero(readBuffer, sizeof(readBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(newPassword, readBuffer);

    strcpy(m.password, crypt(newPassword, HASHKEY));
    write(file, &m, sizeof(m));

    fl1.l_type = F_UNLCK;
    fl1.l_whence = SEEK_SET;
    fl1.l_start = srcOffset;
    fl1.l_len = sizeof(struct Employee);
    fl1.l_pid = getpid();

    fcntl(file, F_UNLCK, &fl1);
    close(file);

    printf("Manager %d changed password\n", mngID);
    return 1;

}