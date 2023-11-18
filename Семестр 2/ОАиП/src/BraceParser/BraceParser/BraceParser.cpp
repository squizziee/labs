#include <iostream>
#include <string>
#include <algorithm>

#define ll long long 

template <typename DT>
class Victor {
private:
	DT* arr;

	ll capacity;
	ll length;

public:
	explicit Victor(ll = 500);


	ll push_back(DT);


	DT pop_back();


	ll size() const;
	DT& operator[](ll);


};


template <typename DT>
Victor<DT>::Victor(ll n) : capacity(n), arr(new DT[n]), length(0)
{
}


template <typename DT>
ll Victor<DT>::push_back(DT data)
{
	if (length == capacity) {
		DT* old = arr;
		arr = new DT[capacity = capacity * 2];
		copy(old, old + length, arr);
		delete[] old;
	}
	arr[length++] = data;
	return length;
}


template <typename DT>
ll Victor<DT>::size() const
{
	return length;
}


template <typename DT>
DT& Victor<DT>::operator[](ll index)
{

	if (index >= length) {
		std::cout << "Error: Array index out of bound";
		exit(0);
	}

	return *(arr + index);
}
template <typename DT>
DT Victor<DT>::pop_back()
{
	return arr[length-- - 1];
}


struct Node {
	std::string  data;
	Node* link;
};

class Stack
{
public:

	void push(Node** head, std::string  data);

	bool isEmpty(Node** head);

	std::string top(Node* node);

	std::string pop(Node* node, Node** head);

};

void Stack::push(Node** head, std::string data)
{
	Node* temp = new Node;

	if (!temp) {
		std::cout << "\nStack Overflow";
		exit(1);
	}

	temp->data = data;

	temp->link = (*head);

	(*head) = temp;
}

bool Stack::isEmpty(Node** head)
{
	return *head == NULL;
}

std::string  Stack::top(Node* node)
{
	if (node == NULL)
	{
		std::cout << "Empty";
		exit(1);
	}
	return node->data;
}

std::string Stack::pop(Node* node, Node** head)
{
	Node* temp = new Node;

	if (*head == NULL) {
		std::cout << "Stack is Empty";
		exit(1);
	}
	else
	{
		std::string get = node->data;
		temp = *head;

		*head = temp->link;

		free(temp);
		return get;
	}
}

int priority(std::string alpha)
{
	char alp = alpha[0];
	if (alp == '+' || alp == '-')
		return 1;
	if (alp == '*' || alp == '/' || alp == '%')
		return 2;
	return 0;
}

std::string convert(Victor<std::string> infix)
{
	int i = 0;
	std::string postfix = "";
	Node* head = NULL;
	Stack s;
	std::string ps = "";
	while (i != infix.size())
	{

		ps = infix[i];

		if (ps[0] == '-' and ps.size() != 1)
		{
			ps.replace(0, 1, "0");//вот здесь на 0 заменяю
		}

		if (ps >= "0" && ps <= "99999999999999999")
		{
			postfix += infix[i];
			postfix += " ";
			i++;
		}
		else if (ps == "(") {
			std::string str = "";
			str += infix[i];
			s.push(&head, str);
			i++;

		}
		else if (ps == ")") {
			while (s.top(head) != "(")
				postfix += s.pop(head, &head);
			s.pop(head, &head);
			i++;
		}
		else {
			while (!s.isEmpty(&head) && priority(ps) <= priority(s.top(head))) {
				postfix += s.pop(head, &head);
			}
			std::string str = "";
			str += infix[i];
			str += " ";
			s.push(&head, str);
			i++;
		}

	}
	while (!s.isEmpty(&head)) {
		postfix += s.pop(head, &head);
	}
	std::cout << "Postfix conversion : " << postfix;
	return postfix;
}

int main() {

	std::string infix = "";
	getline(std::cin, infix);
	infix.erase(std::remove(infix.begin(), infix.end(), ' '), infix.end());

	std::string get_ = "";
	std::string arr = "";

	Victor<std::string> vector;

	for (int i = 0; i < infix.size(); ++i)
	{
		if (infix[i] != ' ') {

			if (infix[i] == '-' and i == 0 or infix[i] == '-' and infix[i - 1] == '(')
			{
				arr += infix[i];
			}
			else if (infix[i] == '(')
			{
				get_ += infix[i];
				vector.push_back(get_);
				get_.clear();
			}
			else if (infix[i] == ')')
			{
				if (arr.size() != 0) {
					vector.push_back(arr);
					arr.clear(); 
				}
				get_ += infix[i];
				vector.push_back(get_);
				get_.clear();
			}
			else
			{
				if (infix[i] != '+' and infix[i] != '-' and infix[i] != '*' and infix[i] != '/' and infix[i] != '%')
				{
					arr += infix[i];
				}
				else
				{
					if (arr.size() != 0) {
						vector.push_back(arr);
						arr.clear();
					}
					get_ += infix[i];
					vector.push_back(get_);
					get_.clear();
				}
			}
		}
	}
	if (arr.size() != 0) vector.push_back(arr);
	std::string get_post = convert(vector);

	Node* head = NULL;
	Stack container;
	Victor<std::string> lox1;
	std::string var;


	for (int i = 0; i < get_post.size(); ++i)
	{
		if (get_post[i] != ' ')
		{
			var += get_post[i];
		}
		else
		{
			lox1.push_back(var);
			var.clear();
		}
	}

	Victor<std::string> reversed;
	for (int i = lox1.size() - 1; i >= 0; --i) {

		reversed.push_back(lox1[i]);
	}

	for (int i = 0; i < reversed.size(); ++i) {

		container.push(&head, reversed[i]);
	}

	long double ans;

	Victor<std::string> storage;
	while (!(container.isEmpty(&head)))
	{
		std::string get_ar = container.pop(head, &head);

		if (get_ar == "+")
		{
			ans = atof(storage[storage.size() - 2].c_str()) + atof(storage[storage.size() - 1].c_str());
			storage.pop_back();
			storage.pop_back();
			storage.push_back(std::to_string(ans));
		}
		else if (get_ar == "-")
		{
			ans = atof(storage[storage.size() - 2].c_str()) - atof(storage[storage.size() - 1].c_str());
			storage.pop_back();
			storage.pop_back();
			storage.push_back(std::to_string(ans));
		}
		else if (get_ar == "*")
		{
			ans = atof(storage[storage.size() - 2].c_str()) * atof(storage[storage.size() - 1].c_str());
			storage.pop_back();
			storage.pop_back();
			storage.push_back(std::to_string(ans));
		}
		else if (get_ar == "/")
		{
			ans = atof(storage[storage.size() - 2].c_str()) / atof(storage[storage.size() - 1].c_str());
			storage.pop_back();
			storage.pop_back();
			storage.push_back(std::to_string(ans));
		}
		else if (get_ar == "%")
		{
			ans = atoi(storage[storage.size() - 2].c_str()) % atoi(storage[storage.size() - 1].c_str());
			storage.pop_back();
			storage.pop_back();
			storage.push_back(std::to_string(ans));
		}
		else
		{
			storage.push_back(get_ar);
		}

	};
	std::cout << std::endl;
	long double result = atof(storage[0].c_str());
	std::cout << "Your result:" << ' ' << result << '\n';

	setlocale(LC_ALL, "Rus");
	if (result == 8)
	{
		std::cout << "--------------♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥-------------" << '\n';

		std::cout << "♥♥♥♥♥♥♥♥♥♥♥♥♥♥ Девочки, с 8 марта вас! ♥♥♥♥♥♥♥♥♥♥♥♥♥" << '\n';

		std::cout << "--------------♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥-------------" << '\n';
	}
	//9 * 8 * (-16 / 2 + 14) / 54
}