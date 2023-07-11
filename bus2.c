#include <stdio.h>
#include <string.h>

struct Seat
{
    char aval[10];
    char reg_name[20];
    int num2;
    int check_aval;
};

struct Bus
{
    int num;
    char name[20];
    int arrive;
    int depart;
    char destination[25];
    struct Seat s1[20];
    int aval;
} b1[10];

void clear_screen()
{
    printf("\033[2J\033[H"); // ANSI escape code to clear screen and move cursor to (0, 0)
}

void pause_program()
{
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

void show_bus()
{
    int x, flag = 0, y;
    printf("Enter Bus Number\n");
    scanf("%d", &x);

    for (int i = 0; i < 10; i++)
    {
        if (x == b1[i].num)
        {
            flag = 1;
            y = i;
            break;
        }
    }

    if (flag == 0)
    {
        printf("Enter correct bus number\n");
        return;
    }

    pause_program();
    clear_screen();

    printf("Bus %d \n", x);
    if (b1[y].aval != 1)
        printf("Available\n");
    else
        printf("Full\n");

    printf("Driver's name: %s \n", b1[y].name);
    printf("Departure Time: %d \n", b1[y].depart);
    printf("Arrival Time: %d \n", b1[y].arrive);
    printf("Destination: %s \n", b1[y].destination);

    pause_program();
    clear_screen();
}

void show_reservations()
{
    int x, flag = 0, y;
    printf("Enter Bus Number\n");
    scanf("%d", &x);

    for (int i = 0; i < 10; i++)
    {
        if (x == b1[i].num)
        {
            flag = 1;
            y = i;
            break;
        }
    }

    if (flag == 0)
    {
        printf("Enter correct bus number\n");
        return;
    }

    pause_program();
    clear_screen();

    printf("Bus %d \n", x);

    for (int i = 0; i < 20; i++)
    {
        if (b1[y].s1[i].check_aval == 1)
            printf("By %s \n", b1[y].s1[i].reg_name);
        else
        {
            strcpy(b1[y].s1[i].reg_name, " ");
            strcpy(b1[y].s1[i].aval, "Available");
        }

        printf("Seat %d \nAvailability: %s \n", i + 1, b1[y].s1[i].aval);

        printf("\n\n");
    }

    pause_program();
    clear_screen();
}

void reserve()
{
    int x, flag = 0, y, a;
    printf("Enter Bus Number\n");
    scanf("%d", &x);

    for (int i = 0; i < 10; i++)
    {
        if (x == b1[i].num)
        {
            flag = 1;
            y = i;
            break;
        }
    }

    if (flag == 0)
    {
        printf("Enter correct bus number\n");
        return;
    }

    pause_program();
    clear_screen();

    printf("Bus %d \n", x);

    printf("Enter Seat Number\n");
    scanf("%d", &a);

    if (a <= 0 || a > 20)
    {
        printf("Enter correct seat number\n");
        return;
    }

    if (b1[y].s1[a - 1].check_aval == 1)
    {
        printf("Sorry seat is already reserved\n");
        pause_program();
        clear_screen();
        return;
    }

    char name2[20];
    printf("Enter your name: ");
    scanf("%s", name2);

    strcpy(b1[y].s1[a - 1].reg_name, name2);
    strcpy(b1[y].s1[a - 1].aval, "Reserved");
    b1[y].s1[a - 1].check_aval = 1;

    pause_program();
    clear_screen();
}

void add_bus()
{
    int count = 0;
    int newBusNum;

    printf("Enter Bus Number: ");
    scanf("%d", &newBusNum);

    // Check if the entered bus number already exists
    for (int i = 0; i < 10; i++)
    {
        if (b1[i].num == newBusNum)
        {
            printf("Bus number already exists. Enter a different bus number.\n");
            return;
        }
    }

    // Find an empty slot in the b1 array
    for (int i = 0; i < 10; i++)
    {
        if (b1[i].num == 0)
        {
            b1[i].num = newBusNum;

            printf("Enter Driver's name: ");
            scanf("%s", b1[i].name);

            printf("Enter Departure Time: ");
            scanf("%d", &b1[i].depart);

            printf("Enter Arrival Time: ");
            scanf("%d", &b1[i].arrive);

            printf("Enter Destination: ");
            getchar(); // consume newline character
            fgets(b1[i].destination, sizeof(b1[i].destination), stdin);

            // ... (Rest of the code to input other bus details)

            printf("Bus added successfully.\n");
            return;
        }
        else
        {
            count++;
        }
    }

    if (count == 10)
    {
        printf("No empty slot available to add a new bus.\n");
    }

    pause_program();
    clear_screen();
}

void remove_bus()
{
    int x, flag = 0, y;
    printf("Enter Bus Number\n");
    scanf("%d", &x);

    for (int i = 0; i < 10; i++)
    {
        if (x == b1[i].num)
        {
            flag = 1;
            y = i;
            break;
        }
    }

    if (flag == 0)
    {
        printf("Enter correct bus number\n");
        return;
    }

    pause_program();
    clear_screen();

    b1[y].num = 0;


}

void delete_reserve()
{
    int busNum, seatNum;
    printf("Enter Bus Number: ");
    scanf("%d", &busNum);

    int busIndex = -1;

    // Find the index of the bus in the b1 array
    for (int i = 0; i < 10; i++)
    {
        if (b1[i].num == busNum)
        {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1)
    {
        printf("Enter correct bus number\n");
        return;
    }

    printf("Enter Seat Number: ");
    scanf("%d", &seatNum);

    if (seatNum <= 0 || seatNum > 20)
    {
        printf("Enter correct seat number\n");
        return;
    }

    if (b1[busIndex].s1[seatNum - 1].check_aval != 1)
    {
        printf("Seat is not reserved\n");
        return;
    }

    // Clear the seat reservation
    strcpy(b1[busIndex].s1[seatNum - 1].reg_name, "");
    strcpy(b1[busIndex].s1[seatNum - 1].aval, "Available");
    b1[busIndex].s1[seatNum - 1].check_aval = 0;

    printf("Seat reservation deleted successfully.\n");
}

void user_menu()
{

    int x = 0;

    while (x <= 4)
    {
        printf("Welcome! Would you like to:\n1.Reserve Bus\n2.Show Reservations\n3.Show Bus Availability\n4.Cancel Booking\n");
        scanf("%d", &x);
        clear_screen();

        switch (x)
        {
        case 1:
            reserve();
            break;
        case 2:
            show_reservations();
            break;
        case 3:
            show_bus();
            break;
        case 4:
            delete_reserve();
            break;
        default:
            x = 5;
            break;
        }
    }
}

void admin_menu()
{
    int z = 0;

    while (z != -1)
    {
        printf("1.Reserve Seat\n2.Show Reservations\n3.Show Bus Availability\n4.Remove Bus\n5.Add Bus\n6.Delete Booking\n");
        scanf("%d", &z);
        clear_screen();

        switch (z)
        {
            case 1:
                reserve();
                break;
            case 2:
                show_reservations();
                break;
            case 3:
                show_bus();
                break;
            case 4:
                remove_bus();
                break;
            case 5:
                add_bus();
                break;
            case 6:
                delete_reserve();
                break;
            default:
                z = -1;
                break;
        }
    }
}

int main()
{
    b1[0].num = 1;
    strcpy(b1[0].name, "Driver1");
    b1[0].arrive = 1200;
    b1[0].depart = 1230;
    strcpy(b1[0].destination, "Sector A");
    strcpy(b1[0].s1[0].aval, "Reserved");
    strcpy(b1[0].s1[0].reg_name, "Ayaan");
    b1[0].s1[0].num2 = 1;
    b1[0].s1[0].check_aval = 1;

    b1[1].num = 2;
    strcpy(b1[1].name, "Driver2");
    b1[1].arrive = 1230;
    b1[1].depart = 1300;
    strcpy(b1[1].destination, "Sector B");
    strcpy(b1[1].s1[0].aval, "Reserved");
    strcpy(b1[1].s1[0].reg_name, "Ayaan");
    b1[1].s1[0].num2 = 1;
    b1[1].s1[0].check_aval = 1;

    b1[2].num = 3;
    strcpy(b1[2].name, "Driver3");
    b1[2].arrive = 1300;
    b1[2].depart = 1330;
    strcpy(b1[2].destination, "Sector C");
    strcpy(b1[2].s1[0].aval, "Reserved");
    strcpy(b1[2].s1[0].reg_name, "Ayaan");
    b1[2].s1[0].num2 = 1;
    b1[2].s1[0].check_aval = 1;

    b1[3].num = 4;
    strcpy(b1[3].name, "Driver4");
    b1[3].arrive = 1330;
    b1[3].depart = 1400;
    strcpy(b1[3].destination, "Sector D");
    strcpy(b1[3].s1[0].aval, "Reserved");
    strcpy(b1[3].s1[0].reg_name, "Ayaan");
    b1[3].s1[0].num2 = 1;
    b1[3].s1[0].check_aval = 1;

    b1[4].num = 5;
    strcpy(b1[4].name, "Driver5");
    b1[4].arrive = 1400;
    b1[4].depart = 1430;
    strcpy(b1[4].destination, "Sector E");
    strcpy(b1[4].s1[0].aval, "Reserved");
    strcpy(b1[4].s1[0].reg_name, "Ayaan");
    b1[4].s1[0].num2 = 1;
    b1[4].s1[0].check_aval = 1;

    for (int i = 0; i < 10; i++)
    {
        int count = 0;
        for (int j = 0; j < 20; j++)
        {
            if (b1[i].s1[j].check_aval == 1)
                count++;
        }

        if (count == 20)
            b1[i].aval = 1;
    }

    int y = 0;

    while (y != -1)
    {
        printf("Are you:\n1.User\n2.Admin\n");
        scanf("%d", &y);

        switch (y)
        {
            case 1:
                user_menu();
                break;
            case 2:
                admin_menu();
                break;
            default:
                y = -1;
                return 0;
                break;
        }
    }


    return 0;
}
