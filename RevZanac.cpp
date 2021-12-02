void topView(Node* root) {
    if (root == NULL) {
        return;
    }
    //si el nodo mas alto ya fue visitado lo hasheamos para ver si se vio o no
    queue<Node*> q;
    map<int, int> mapa;
    int header = 0;
    root->header = header;
    //se asigna mi root como primera instancia de mi q de manera horizontal
    q.push(root);
    //mientras haya algo dentro de la q
    while (q.size()) {
        //mi header = root
        header = root->header;
        //mapa.count regresa 1 si es = a header, sino se manda el dato 
        if (mapa.count(header) == 0) {
            mapa[header] = root->dato;
        }
        //condicion de que pasa con mi izq
        if (root->izq) {
            root->izq->header = header - 1;
            q.push(root->izq);
        }
        //condicion de que pasa con der
        if (root->der) {
            root->der->header = header + 1;
            q.push(root->der);
        }

        q.pop();
        //first in first out, se reasigna mi root como el ultimo en q
        root = q.front();
    }
    for (auto i = mapa.begin(); i != mapa.end(); i++) {
        cout << i->second << " ";
    }
}