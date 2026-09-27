use std::collections::LinkedList;

pub type ListaEnlazada = LinkedList<(usize, i32)>;

pub fn insertar(lista: &mut ListaEnlazada, clave: usize, valor: i32) {
    for par in lista.iter_mut() {
        if par.0 == clave {
            par.1 = valor;
            return;
        }
    }

    lista.push_back((clave, valor));
}

pub fn buscar(lista: &ListaEnlazada, clave: usize) -> Option<i32> {
    for par in lista.iter() {
        if par.0 == clave {
            return Some(par.1);
        }
    }

    None
}

pub fn eliminar(lista: &mut ListaEnlazada, clave: usize) {
    let mut nueva_lista = LinkedList::new();

    while let Some(par) = lista.pop_front() {
        if par.0 != clave {
            nueva_lista.push_back(par);
        }
    }

    *lista = nueva_lista;
}