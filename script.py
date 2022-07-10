import x_clicker
import time

direction = 1

for i in range(10):
    if i >= 5:
        direction = -1

    x_clicker.move_pointer(10 * direction, 20 * direction)
    time.sleep(0.1)


print(x_clicker.get_position())
print(x_clicker.get_color())
print("The end")
