#include <iostream>
#include "Map.h"
#include "Robot.h"
#include "Game.h"
#include <string.h>
using namespace std;
int Robot::total_robots = 0;
int main() {

    Map map1(1);
    Map map2(2);
    Map mapi(2);
    Game game(map1, map2);
    int add_flag=0;

    //first row
    map1.setCoordinate(0, 0, 1);
    map1.setCoordinate(1, 0, 0);
    map1.setCoordinate(2, 0, 0);
    map1.setCoordinate(3, 0, 0);
    map1.setCoordinate(4, 0, 0);
    map1.setCoordinate(5, 0, 0);
    map1.setCoordinate(6, 0, 0);
    //second row
    map1.setCoordinate(0, 1, 1);
    map1.setCoordinate(1, 1, 0);
    map1.setCoordinate(2, 1, 1);
    map1.setCoordinate(3, 1, 0);
    map1.setCoordinate(4, 1, 0);
    map1.setCoordinate(5, 1, 1);
    map1.setCoordinate(6, 1, 0);
    //third row
    map1.setCoordinate(0, 2, 1);
    map1.setCoordinate(1, 2, 0);
    map1.setCoordinate(2, 2, 1);
    map1.setCoordinate(3, 2, 1);
    map1.setCoordinate(4, 2, 0);
    map1.setCoordinate(5, 2, 1);
    map1.setCoordinate(6, 2, 0);
    //fourth row
    map1.setCoordinate(0, 3, 0);
    map1.setCoordinate(1, 3, 0);
    map1.setCoordinate(2, 3, 0);
    map1.setCoordinate(3, 3, 1);
    map1.setCoordinate(4, 3, 1);
    map1.setCoordinate(5, 3, 1);
    map1.setCoordinate(6, 3, 0);
    //fifth row
    map1.setCoordinate(0, 4, 0);
    map1.setCoordinate(1, 4, 1);
    map1.setCoordinate(2, 4, 0);
    map1.setCoordinate(3, 4, 1);
    map1.setCoordinate(4, 4, 1);
    map1.setCoordinate(5, 4, 1);
    map1.setCoordinate(6, 4, 0);
    // sixth
    map1.setCoordinate(0, 5, 1);
    map1.setCoordinate(1, 5, 1);
    map1.setCoordinate(2, 5, 0);
    map1.setCoordinate(3, 5, 0);
    map1.setCoordinate(4, 5, 0);
    map1.setCoordinate(5, 5, 0);
    map1.setCoordinate(6, 5, 1);

    map1.setCoordinate(0, 6, 1);
    map1.setCoordinate(1, 6, 0);
    map1.setCoordinate(2, 6, 0);
    map1.setCoordinate(3, 6, 1);
    map1.setCoordinate(4, 6, 1);
    map1.setCoordinate(5, 6, 0);
    map1.setCoordinate(6, 6, 1);

    map2.setCoordinate(0, 0, 1);
    map2.setCoordinate(1, 0, 0);
    map2.setCoordinate(2, 0, 1);
    map2.setCoordinate(3, 0, 0);
    map2.setCoordinate(4, 0, 0);
    map2.setCoordinate(5, 0, 0);
    map2.setCoordinate(6, 0, 0);
    //second row
    map2.setCoordinate(0, 1, 1);
    map2.setCoordinate(1, 1, 1);
    map2.setCoordinate(2, 1, 0);
    map2.setCoordinate(3, 1, 1);
    map2.setCoordinate(4, 1, 1);
    map2.setCoordinate(5, 1, 1);
    map2.setCoordinate(6, 1, 0);
    //third row
    map2.setCoordinate(0, 2, 0);
    map2.setCoordinate(1, 2, 0);
    map2.setCoordinate(2, 2, 0);
    map2.setCoordinate(3, 2, 0);
    map2.setCoordinate(4, 2, 0);
    map2.setCoordinate(5, 2, 1);
    map2.setCoordinate(6, 2, 1);
    //fourth row
    map2.setCoordinate(0, 3, 0);
    map2.setCoordinate(1, 3, 1);
    map2.setCoordinate(2, 3, 1);
    map2.setCoordinate(3, 3, 1);
    map2.setCoordinate(4, 3, 0);
    map2.setCoordinate(5, 3, 1);
    map2.setCoordinate(6, 3, 1);
    //fifth row
    map2.setCoordinate(0, 4, 1);
    map2.setCoordinate(1, 4, 1);
    map2.setCoordinate(2, 4, 0);
    map2.setCoordinate(3, 4, 0);
    map2.setCoordinate(4, 4, 0);
    map2.setCoordinate(5, 4, 1);
    map2.setCoordinate(6, 4, 1);
    // sixth
    map2.setCoordinate(0, 5, 1);
    map2.setCoordinate(1, 5, 1);
    map2.setCoordinate(2, 5, 0);
    map2.setCoordinate(3, 5, 1);
    map2.setCoordinate(4, 5, 1);
    map2.setCoordinate(5, 5, 1);
    map2.setCoordinate(6, 5, 1);

    map2.setCoordinate(0, 6, 1);
    map2.setCoordinate(1, 6, 1);
    map2.setCoordinate(2, 6, 0);
    map2.setCoordinate(3, 6, 0);
    map2.setCoordinate(4, 6, 0);
    map2.setCoordinate(5, 6, 1);
    map2.setCoordinate(6, 6, 1);


    char ch[300];
    while (strcmp(&ch[0], "9") != 0) {
        printf("Robot Control Menu \n");
        printf("1. Add Robot \n");
        printf("2. Delete Robot \n");
        printf("3. Move Robot \n");
        printf("4. Operator + \n");
        printf("5. Operator += \n");
        printf("6. Operator = \n");
        printf("7. Operator == \n");
        printf("8. Operator << \n");
        printf("9. Quit \n");
        printf("Input your option: \n");
        scanf("%s", ch);
        if (strlen(ch) > 1) {
            printf("Invalid input \n");
            continue;
        }

        switch (ch[0]) {
            // how to handle in case of to 2 robots in same location
            case '1': {
                int col;
                int row;
                int map_number;
                printf("Enter MAP number: \n");
                scanf("%d", &map_number);
                if (map_number != 2 && map_number != 1) {
                    printf("Invalid MAP number \n");
                    break;
                }
                printf("Enter Coordinates (X,Y): \n");
                scanf("%d %d", &col, &row);
                if (!game.AddRobot(map_number, col, row))
                    printf("Invalid location \n");
                else {
                    add_flag = 1;
                    cout << "New " << *game.getRobotArray()[game.getRobotAmount() - 1];
                }
                break;
            };

            case '2': {
                int robot_number;
                printf("Enter Robot number: \n");
                scanf("%d", &robot_number);
                Robot *search_result = game.RobotFinder(robot_number);
                if (search_result != nullptr) {
                    cout << "\nRobot deleted: " << robot_number << " MAP: " << (*search_result).getMapNumber()
                         << " GPS: " << (*search_result).getCoordinateCol() << ","
                         << (*search_result).getCoordinateRow() << "\n";
                    game.DeleteRobot(robot_number);

                } else
                    printf("Invalid input \n");
                break;
            };

            case '3': {
                int robot_number;
                char direction;
                printf("Enter Robot number: \n");
                scanf("%d", &robot_number);
                printf("Enter Direction: \n");
                scanf("%s", &direction);
                if (!game.MoveRobot(robot_number, direction)) break;
                else cout << *(game.RobotFinder(robot_number));
                break;
            };

            case '4': {
                Map temp_map = map1 + map2;
                cout << temp_map << "\n";
                if(game.getRobotAmount()>0) {
                    for (int i = 0; i < game.getRobotAmount(); i++)
                        if (temp_map.getCoordinate((*game.getRobotArray()[i]).getCoordinateCol(),
                                                   (*game.getRobotArray()[i]).getCoordinateRow()) == 0)
                            cout << "Robot: " << (*game.getRobotArray()[i]).getRobotNumber() << " GPS: "
                                 << (*game.getRobotArray()[i]).getCoordinateCol() << ","
                                 << (*game.getRobotArray()[i]).getCoordinateRow() << "\n";
                }
                break;

            };

            case '5': {
                int override_map;
                Map *chosen_map;
                printf("Override MAP number: \n");
                scanf("%d", &override_map);
                if (override_map != 1 && override_map != 2) {
                    printf("Invalid MAP number: \n");
                    break;
                }
                if (override_map == 1) {
                    map1 += map2;
                    chosen_map = &map1;
                }
                if (override_map == 2) {
                    map2 += map1;
                    chosen_map = &map2;
                }
                for (int i = 0; i < game.getRobotAmount(); i++) {
                    if (chosen_map->getCoordinate((*game.getRobotArray()[i]).getCoordinateCol(),
                                                  (*game.getRobotArray()[i]).getCoordinateRow()) == 1) {
                        game.DeleteRobot((*game.getRobotArray()[i]).getRobotNumber());
                        i--;
                    }
                }
                break;
            }
            case '6': {
                int override_map;
                Map *chosen_map;
                printf("Override MAP number:\n");
                scanf("%d", &override_map);
                if (override_map != 1 && override_map != 2) {
                    printf("Invalid MAP number\n");
                    break;
                }
                if (override_map == 1) {
                    map1 = map2;
                    chosen_map = &map1;
                }
                if (override_map == 2) {
                    map2 = map1;
                    chosen_map = &map2;
                }

                for (int i = 0; i < game.getRobotAmount(); i++) {
                    if (chosen_map->getCoordinate((*game.getRobotArray()[i]).getCoordinateCol(),(*game.getRobotArray()[i]).getCoordinateRow()) == 1) {
                        game.DeleteRobot((*game.getRobotArray()[i]).getRobotNumber());
                        i--;
                    }
                }
                break;
            }
            case '7': {
                bool result = map1 == map2;
                if (result == 0)
                    cout << "FALSE\n";
                else
                    cout << "TRUE\n";
                break;
            }

            case '8': {
                int map_number;
                printf("Please enter MAP number:\n");
                scanf("%d", &map_number);
                if(map_number != 1 && map_number != 2) {
                    printf("Invalid MAP number\n");
                    break;
                }
                cout << game.getMap(map_number) << "\n";

                for (int i = 0; i < game.getRobotAmount(); i++) {
                    if (game.getRobotArray()[i]->getMapNumber() == map_number &&
                        game.getRobotArray()[i]->getOutFlag() == 0)
                        cout << *game.getRobotArray()[i];
                }
                break;
            };
            case '9':{
                break;
            }
            default:{
                printf("Invalid input \n");
                break;
            }


        }
    }

    return 0;
}
