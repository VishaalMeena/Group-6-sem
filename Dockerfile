# Use an official GCC image as the base image
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /usr/src/app

# Copy the current directory's contents into the container
COPY . .

# Compile the C++ program (assuming your main file is named main.cpp)
RUN g++ -o online_exam_system main.cpp

# Run the compiled executable when the container starts
CMD ["./online_exam_system"]
