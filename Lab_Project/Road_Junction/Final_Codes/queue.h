#ifndef QUEUE_H
#define QUEUE_H


typedef struct ItemType
{
	int id_;
	ItemType *next_;
} Item;


class Queue
{
	public:
		Queue ();
		inline int& length () { return (length_); }
		void enque (Item *im);
		Item* deque ();

	private:
		int length_;
		Item *head_;
		Item *tail_;
};


#endif // QUEUE_H
