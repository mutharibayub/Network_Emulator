#include "./Header.h"

int main()
{

	string input = "";
	cout << "Would you like to use \"List\" or \"Splay Tree\" to save the routing tables of routers?\n";
	while (true)
	{

		cout << "Enter \"list\" or \"splay\": ";
		getline(cin, input);
		input = lowerStr(input);
		if (input == "list" || input == "splay")
		{
			break;
		}
	}

	Network n(input);
	n.populateLists("network.csv");
	n.makeGraph("network.csv");
	n.updateRoutingTable();

	thread t(&Network::routerSimThread, ref(n));
	while (true) {
		string cmd;
		cout << ">>> ";
		getline(cin, cmd);
		if (lowerStr(cmd) == "exit") { // simple exit condition, just for testing
			break;
		}
		queue_lock.lock();
		cmds.enqueue(cmd);
		queue_lock.unlock();
	}

	t.detach(); // "detach" the thread so c++ stop's throwing exceptions when program exits..
}
