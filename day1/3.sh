#!/bin/bash
# Convert distance into meters, centimeters, and kilometers

read -p "Enter distance in kilometers: " km

meters=$(echo "$km * 1000" | bc)
centimeters=$(echo "$km * 100000" | bc)

echo "Distance in Kilometers: $km"
echo "Distance in Meters: $meters"
echo "Distance in Centimeters: $centimeters"
