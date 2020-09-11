#include <iostream>
#include <cstdlib>
using namespace std;

class node {
private:
	node* prev;
	node* next;
	int current;
	int target;

public:
	node() : prev(NULL), next(NULL), current(0), target(0) {}

	void setTarget(int t) {
		this->target = t;
	}

	int getTarget() {
		return this->target;
	}

	void setCurrent(int c) {
		this->current = c;
	}

	int getCurrent() {
		return this->current;
	}

	void setNext(node* n) {
		this->next = n;
	}

	node* getNext() {
		return this->next;
	}

	void setPrev(node* n) {
		this->prev = n;
	}

	node* getPrev() {
		return this->prev;
	}

	friend class elevator;
};

class PQueue {
private:
	node* front;
	int size;
	int flag; //0 for down //1 for up
	string name;

public:
	PQueue(int flag, string name) {
		front = NULL;
		size = 0;
		this->flag = flag;
		this->name = name;
	}

	void enqueue(int target) {
		node* newNode = new node;
		newNode->setTarget(target);

		if (isEmpty()) {
			front = newNode;
			return;
		}

		if (flag == 1) {
			if (target < front->getTarget()) {
				front->setPrev(newNode);
				newNode->setPrev(NULL);
				newNode->setNext(front);
				front = newNode;
				return;
			}
			node* temp = front;
			for (; temp->getNext() != NULL && temp->getNext()->getTarget() <= target; temp = temp->getNext());
			if (temp->getTarget() != newNode->getTarget()) {
				newNode->setNext(temp->getNext());
				temp->setNext(newNode);
			}
			return;
		}

		if (flag == 0) {
			if (target > front->getTarget()) {
				front->setPrev(newNode);
				newNode->setPrev(NULL);
				newNode->setNext(front);
				front = newNode;
				return;
			}
			node* temp = front;
			for (; temp->getNext() != NULL && temp->getNext()->getTarget() >= target; temp = temp->getNext());
			if (temp->getTarget() != newNode->getTarget()) {
				newNode->setNext(temp->getNext());
				temp->setNext(newNode);
			}
			return;
		}
	}

	void display() { //test only
		node* temp = front;
		
		if (isEmpty()) {
			printf("%s", name.c_str());
			cout << " Queue is Empty!" << endl;
			return;
		}

		while (temp != NULL) {
			printf("%s", name.c_str());
			cout << " Queue: " << temp->getTarget() << endl;
			temp = temp->getNext();
		}
	}

	bool isEmpty() {
		return (front == NULL);
	}

	void dequeue() {
		if (isEmpty()) {
			size = 0;
			cout << "PQueue is Empty!" << endl;
			return;
		}

		node* temp;
		temp = front;
		front = front->getNext();
		delete temp;
		size--;
	}

	friend class elevator;
};

class elevator {
private:
	int elevatorPosition = 0;
	PQueue *x; //up
	PQueue *y; //down
	PQueue *c;
public:
	elevator() {
		x = new PQueue(1, "Up");
		y = new PQueue(0, "Down");
		c = new PQueue(1, "Current");
	}

	void request() {
		int current;
		int target;

		cout << "Please enter your current floor : ";
		cin >> current;
		cout << "Please enter your target floor : ";
		cin >> target;
		
		while (current != -1 && target != -1) {
			
			if (!(current==target)) {
				c->enqueue(current);

				if (current > target) {
					y->enqueue(target);
				}

				if (current < target) {
					x->enqueue(target);
				}
			}

			cout << "Please enter your current floor : ";
			cin >> current;
			cout << "Please enter your target floor : ";
			cin >> target;
		}

		start();
	}

	void start() {
		while (!(c->isEmpty())) {
			if (!(x->isEmpty())) {
				if (c->front->getTarget() < x->front->getTarget()) {
					elevatorPosition = c->front->getTarget();
					c->dequeue();
				}
				else if (c->front->getTarget() > x->front->getTarget()) {
					elevatorPosition = x->front->getTarget();
					x->dequeue();
				}
				else {
					elevatorPosition = x->front->getTarget();
					x->dequeue();
					c->dequeue();
				}
			}
			else {
				if (!(y->isEmpty())) {
					if (c->front->getTarget() > y->front->getTarget()) {
						elevatorPosition = c->front->getTarget();
						c->dequeue();
					}
					else if (c->front->getTarget() < y->front->getTarget()) {
						elevatorPosition = y->front->getTarget();
						y->dequeue();
					}
					else {
						elevatorPosition = y->front->getTarget();
						y->dequeue();
						c->dequeue();
					}
				}
			}

			reviewElevator();
		}

		while (!(x->isEmpty())) {
			elevatorPosition = x->front->getTarget();
			x->dequeue();
			reviewElevator();
		}

		while (!(y->isEmpty())) {
			elevatorPosition = y->front->getTarget();
			y->dequeue();
			reviewElevator();
		}
	}

	void reset() {
		elevatorPosition = 0;
	}

	int getElevatorPosition() {
		return elevatorPosition;
	}

	void reviewElevator() {
		cout << "\nCurrent elevator position: " << this->getElevatorPosition() << endl;
		c->display();
		x->display();
		y->display();
	}

	friend class node;
	friend class PQueue;
};

int main() {

	cout << "-- ELEVATOR SIMULATION PROJECT --\n" << endl;
	
	cout << "###### INSTRUCTION ######" << endl;
	cout << "Please enter all the requests needed to be performed" << endl;
	cout << "To terminate, please enter \"- 1\" in the request\n" << endl;

	cout << "\n###### SIMULATOR ######" << endl;

	elevator a;
	int input;

	do {
		a.request();
		cout << "For new request press any key, to terminate please press -1" << endl;
		cin >> input;
		cout << endl;
	} while (input != -1);

	cout << "\n###### CREDITS ######" << endl;
	cout << "ELEVATOR SIMULATOR V1.5" << endl;
	cout << "Created by: " << endl;
	cout << "Mohamed El Ghamry" << endl << "Mostafa Hazem" << endl << "Mahmoud Khalil" << endl;
	cout << "~(3M Group)~\n" << endl;

	system("pause");
	return 0;
}