template<typename T>
class Node
{
public:
	Node<T>* next;
	T element;

	Node(T* element)
	{
		this->element = *element;
		this->next = NULL;
	}
};