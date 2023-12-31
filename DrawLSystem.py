# import turtle
#
# def calculate_bounds(commands, distance):
#     r_x,l_x,up_y,down_y = 0,0,0,0
#     direction = 0
#     dir =['u','d','l','r']
#     max_up_y, max_down_y,max_l_x,max_r_x = 0,0,0,0
#     for cmd in commands:
#         if cmd == 'F':
#             direction = dir[3]
#         elif cmd == '+':
#             direction = dir[1]
#         elif cmd == '-':
#             direction = dir[0]
#         break
#
#     for cmd in commands:
#         if cmd == 'F':
#             if direction == 'u':
#                 up_y += distance
#                 down_y -= distance
#                 if up_y > max_up_y:
#                     max_up_y = up_y
#             elif direction == 'd':
#                 down_y += distance
#                 up_y -= distance
#                 if down_y > max_down_y:
#                     max_down_y = down_y
#             elif direction == 'l':
#                 l_x += distance
#                 r_x -= distance
#                 if l_x > max_l_x:
#                     max_l_x = l_x
#             else:
#                 r_x += distance
#                 l_x -= distance
#                 if r_x > max_r_x:
#                     max_r_x = r_x
#
#         elif cmd == '+':
#             if direction == 'u':
#                 direction = dir[3]
#             elif direction == 'd':
#                 direction = dir[2]
#             elif direction == 'l':
#                 direction = dir[0]
#             else:
#                 direction = dir[1]
#
#         elif cmd == '-':
#             if direction == 'u':
#                 direction = dir[2]
#             elif direction == 'd':
#                 direction = dir[3]
#             elif direction == 'l':
#                 direction = dir[1]
#             else:
#                 direction = dir[0]
#
#     return max_up_y, max_down_y,max_l_x,max_r_x
#
# def center_turtle(screen_width, screen_height,max_up_y, max_down_y,max_l_x,max_r_x,breedte,hoogte):
#     print('max_r_x',max_r_x)
#     startx = max_r_x
#     print('max_down_y', max_down_y)
#     starty =  -max_down_y
#     print('startx', startx)
#     print('starty', starty)
#     print()
#     print()
#     return startx, starty
#
# def draw_lsystem(filename, distance, angle):
#     print('drawing ...')
#     with open(filename, "r") as file:
#         commands = file.read()
#
#     max_up_y, max_down_y,max_l_x,max_r_x = calculate_bounds(commands, distance)
#     breedte = max_r_x + max_l_x + 1000
#     hoogte = max_up_y + max_down_y + 1000
#     start_x, start_y = center_turtle(turtle.window_width(), turtle.window_height(), max_up_y, max_down_y,max_l_x,max_r_x,breedte,hoogte)
#     print('y_up',max_up_y)
#     print('y_down',max_down_y)
#     print('x_left',max_l_x)
#     print('x_right',max_r_x)
#     print('breedte',breedte)
#     print('startx',start_x)
#     print('hoogte',hoogte)
#     print('starty',start_y)
#     breedte += 200
#     hoogte += 100
#     t = turtle.Turtle()
#     t.speed(100)
#     t.up()
#     turtle.setup(width=breedte, height=hoogte)
#     t.goto(start_x, start_y)
#     t.right(90)
#     t.down()
#
#
#
#     for cmd in commands:
#         print(t.xcor(),t.ycor())
#         if cmd == 'F':
#             t.forward(distance)
#         elif cmd == '+':
#             t.right(angle)
#         elif cmd == '-':
#             t.left(angle)
#     print('drawing done!')
#
#     turtle.done()

import turtle


# def calculate_bounds(commands, distance, angle):
#     min_x, max_x, min_y, max_y = 0, 0, 0, 0
#     x, y, direction = 0, 0, 0
#
#     for cmd in commands:
#         if cmd == 'F':
#             x += distance * math.cos(math.radians(direction))
#             y += distance * math.sin(math.radians(direction))
#             min_x, max_x = min(min_x, x), max(max_x, x)
#             min_y, max_y = min(min_y, y), max(max_y, y)
#         elif cmd == '+':
#             direction += angle
#         elif cmd == '-':
#             direction -= angle
#
#     return min_x, max_x, min_y, max_y


def draw_lsystem(filename, distance, angle):
    with open(filename, "r") as file:
        commands = file.read()

    #min_x, max_x, min_y, max_y = calculate_bounds(commands, distance, angle)

    # Adjust the window size
    screen = turtle.Screen()
    # screen_width = round(max_x - min_x + 20)
    # screen_height = round(max_y - min_y + 20)
    #screen.setup(width=screen_width+300, height=screen_height+150)


    # Start the turtle at the top-left corner of the bounds
    # start_x = round(-screen_width / 2 + 10)
    # start_y = round(screen_height / 2 - 10)

    t = turtle.Turtle()
    t.speed("fastest")
    t.up()
    turtle.setup(width=600, height=800)
    t.goto(0, 0)
    t.down()
    print('drawing ...')
    t.setheading(90)  # Initial heading

    stack = []  # Stack to store the turtle's position and heading

    for cmd in commands:
        if cmd == 'F':
            t.forward(distance)
        elif cmd == '+':
            t.right(angle)
        elif cmd == '-':
            t.left(angle)
        elif cmd == '[':
            # Save the current state (position and heading)
            stack.append((t.position(), t.heading()))
        elif cmd == ']':
            # Restore the saved state
            position, heading = stack.pop()
            t.up()  # Lift the pen before moving
            t.setposition(position)
            t.setheading(heading)
            t.down()
    print('drawing done!')
    turtle.done()

# Assuming you have a screen size of 800x600 or similar
draw_lsystem("C:\\Users\\Mateo\\CLionProjects\\Ba2S1_Data_Structures\\7_Project\\outputFile\\lsystem_output.txt",2, 30)
