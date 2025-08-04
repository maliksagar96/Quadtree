import matplotlib.pyplot as plt

# Read file
rectangles = []
with open("rootNode.txt") as f:
    for line in f:
        parts = line.strip().split()
        xmin = float(parts[0])
        xmax = float(parts[1])
        ymin = float(parts[2])
        ymax = float(parts[3])
        leaf_id = int(parts[4])
        rectangles.append((xmin, xmax, ymin, ymax, leaf_id))

# Plot
fig, ax = plt.subplots()
for xmin, xmax, ymin, ymax, leaf_id in rectangles:
    width = xmax - xmin
    height = ymax - ymin
    ax.add_patch(plt.Rectangle((xmin, ymin), width, height,
                 fill=False, edgecolor='black'))
    
    # Annotate leaf_id at the center
    cx = (xmin + xmax) / 2
    cy = (ymin + ymax) / 2
    ax.text(cx, cy, str(leaf_id), ha='center', va='center', fontsize=8)

ax.set_aspect('equal')
plt.show()
