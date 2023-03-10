#include <iostream>
#include <queue>
using namespace std;

class Library {
private:
    queue<int> student_queue;
    queue<int> teacher_queue;
public:
    void enqueue(string visitor_type, int visitor_id) {
        if (visitor_type == "student") {
            student_queue.push(visitor_id);
        } else if (visitor_type == "teacher") {
            teacher_queue.push(visitor_id);
        }
    }
    
    int dequeue(string visitor_type) {
        if (visitor_type == "student") {
            int visitor_id = student_queue.front();
            student_queue.pop();
            return visitor_id;
        } else if (visitor_type == "teacher") {
            int visitor_id = teacher_queue.front();
            teacher_queue.pop();
            return visitor_id;
        }
        return -1; // Invalid visitor type
    }
    
    void process_queue() {
        bool teacher_waiting = false;
        string currently_serving = "student";
        
        while (!student_queue.empty() || !teacher_queue.empty()) {
            if (currently_serving == "teacher" && teacher_queue.empty()) {
                currently_serving = "student";
            }
            
            if (currently_serving == "student") {
                if (teacher_waiting) {
                    currently_serving = "teacher";
                    teacher_waiting = false;
                } else {
                    currently_serving = teacher_queue.empty() ? "student" : "teacher";
                }
            }
            
            if (currently_serving == "teacher" && !teacher_waiting) {
                teacher_waiting = !student_queue.empty();
            }
            
            int visitor_id = dequeue(currently_serving);
            cout << "Processing " << currently_serving << " with ID " << visitor_id << endl;
        }
    }
};

int main() {
    Library library;

    library.enqueue("student", 1);
    library.enqueue("student", 2);
    library.enqueue("teacher", 1);

    library.process_queue();

    return 0;
}
