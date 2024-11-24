    vector<bool> checked(SIZE, false);  // Track visited nodes
        stack<int> temp;  // Stack to perform DFS
        temp.push(start);
        cout << "DFS starting from vertex " << start << ":" << endl;

        while (!temp.empty()) {
            int i = temp.top();
            temp.pop();

            if (!checked[i]) {
                cout << i << " ";  // Print the current node
                checked[i] = true;

                // Push neighbors onto the stack, sorted in reverse order to match expected DFS
                for (auto it = adjList[i].rbegin(); it != adjList[i].rend(); ++it) {
                    if (!checked[it->first]) {
                        temp.push(it->first);
                    }
                }
            }
        }
        cout << "\n";