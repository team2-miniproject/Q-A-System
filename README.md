# Q&A System (C++ with Sockets)

This is a simple **Q&A system** built using **C++ and sockets**. Users can **register, log in, ask questions, answer questions, and store interactions** in files.

---

## Features
✅ **User Registration & Login** (with unique usernames)  
✅ **Question Submission** (stored with a unique ID and username)  
✅ **Answer Submission** (linked to a question ID and username)  
✅ **File-based Storage** (`questions.txt` & `answers.txt`)  
✅ **Multi-Client Support** using **multithreading**

---

## Installation & Setup
### **1. Compile the Server**
```sh
make clean
make
```

### **2. Run the Server**
```sh
./server
```

### **3. Run the Client**
```sh
./client
```

---

## How to Use
### **User Registration**
1. Select **Register** when prompted.
2. Enter a unique username & password.
3. If the username already exists, registration will fail.

### **User Login**
1. Select **Login** when prompted.
2. Enter username & password.
3. If credentials are correct, login succeeds.

### **Asking a Question**
1. Select **"Ask a Question"** from the menu.
2. Enter your question.
3. The question is saved in `questions.txt` with a unique **Question ID** and **Username**.

### **Answering a Question**
1. Select **"Answer a Question"** from the menu.
2. A list of available questions (with their IDs and usernames) is displayed.
3. Enter the **Question ID** to which you want to respond.
4. Type your answer.
5. The answer is stored in `answers.txt` with a unique **Answer ID**, **Question ID**, and **Username**.

---

## File Format
### **questions.txt**
```
<Question ID> <Username> <Question Text>
```
**Example:**
```
1 alice What is a socket in networking?
2 bob How does multithreading work?
```

### **answers.txt**
```
<Answer ID> <Question ID> <Username> <Answer Text>
```
**Example:**
```
1 1 bob A socket is an endpoint for communication between two machines.
2 2 alice Multithreading allows multiple tasks to run concurrently.
```

---

## Future Improvements
- Implement **Search Functionality** for questions.
- Add **Upvote/Downvote System** for answers.
- Store passwords securely using **hashing**.
- Implement **Admin Controls** to moderate content.

---

## Author
Developed by **Group 2** as part of an **Operating Systems** mini project. 

