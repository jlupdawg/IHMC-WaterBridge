from HaversineFunction import haversine
from BearingAngleFunction import calculate_initial_compass_bearing

lonCurrent = 87.19325
latCurrent = 30.50188

lonWant = 87.19265
latWant = 30.50020

print(str(haversine(lonCurrent, latCurrent, lonWant, latWant)) + " feet")
print(str(calculate_initial_compass_bearing(lonCurrent, latCurrent, lonWant, latWant)) + " Degrees")
