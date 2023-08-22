# Design a Ride Sharing Application

You have been tasked with designing a ride-sharing application similar to services like Uber, Lyft, or Ola. The application will allow drivers to offer rides with information about the origin, destination, and number of available seats. Riders can request rides by providing their desired origin, destination, and number of seats. The application should also calculate the ride amount based on the distance and the number of seats, applying specific algorithms for pricing.

# Design Requirements:

1. **Driver and Rider Management:**
   - The application should support the addition of multiple drivers and riders.
   - Drivers can offer rides with details including origin, destination, and the number of available seats.
   - Riders can request rides by specifying their desired origin, destination, and the number of seats they need.

2. **Ride Management:**
   - The application should support the creation and updating of rides.
   - A rider can withdraw a requested ride before it is confirmed.

3. **Ride Amount Calculation:**
   - The ride amount is calculated based on the distance between the origin and destination, and the number of seats.
   - If the number of seats is 1, the ride amount is calculated as (Distance * Amount Charged per KM).
   - If the number of seats is 2 or more, the ride amount is calculated as (Distance * Number of Seats * 0.75 * Amount Charged per KM).

4. **Preferred Rider Bonus:**
   - A rider becomes a preferred rider after completing more than 10 rides.
   - Preferred riders receive a discount on the ride amount.
   - If the number of seats is 1, the preferred ride amount is calculated as (Distance * Amount Charged per KM * 0.75).
   - If the number of seats is 2 or more, the preferred ride amount is calculated as (Distance * Number of Seats * 0.5 * Amount Charged per KM).

# Functionalities Expected:

- Add Driver: Add a new driver to the application.
- Add Rider: Add a new rider to the application.
- Create Ride: Create a ride request with details such as origin, destination, and number of seats.
- Update Ride: Modify the details of an existing ride.
- Withdraw Ride: Allow riders to withdraw a requested ride before it is confirmed.
- Calculate Ride Amount: Calculate the ride amount based on distance, number of seats, and rider type (preferred or regular).

# Bonus Features (Good to Have):

- Upgrade to Preferred Rider: Riders become preferred riders after completing more than 10 rides.
- Apply Preferred Rider Bonus: Calculate ride amount with discounts for preferred riders.

# Test Case Example:

- Rider A requests a ride (origin: 50, destination: 60, seats: 1).
  - Output: Ride Amount = 10 * 20 (Amount/Km) = 200
- Rider A requests a ride (origin: 50, destination: 60, seats: 2).
  - Output: Ride Amount = 10 * 2 * 0.75 * 20 (Amount/Km) = 300

# UML Diagram : 
![Screenshot (784)](https://github.com/hksirya/LowLevelDesign/assets/104431269/afd28891-d868-4ab0-8a48-faa703a16de3)
# Output :
![Screenshot (786)](https://github.com/hksirya/LowLevelDesign/assets/104431269/ba041b1d-7a2a-48b4-bba2-13a519a6dc82)

