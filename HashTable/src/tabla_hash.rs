use crate::lista_enlazada::{ListaEnlazada,
    insertar as insertar_lista,
    buscar as buscar_lista,
    eliminar as eliminar_lista,
};

pub fn funcion_hash(clave: usize, tamanio: usize) -> usize {
    clave % tamanio
}

pub fn crear(tamanio: usize) -> Vec<ListaEnlazada> {
    vec![ListaEnlazada::new(); tamanio]
}

pub fn insertar(tabla: &mut Vec<ListaEnlazada>,clave: usize,valor: i32,) {
    let indice = funcion_hash(clave, tabla.len());

    insertar_lista(&mut tabla[indice], clave, valor);
}

pub fn buscar(tabla: &Vec<ListaEnlazada>,clave: usize,) -> Option<i32> {
    let indice = funcion_hash(clave, tabla.len());

    buscar_lista(&tabla[indice], clave)
}

pub fn eliminar(tabla: &mut Vec<ListaEnlazada>,clave: usize,) {
    let indice = funcion_hash(clave, tabla.len());

    eliminar_lista(&mut tabla[indice], clave);
}

pub fn mostrar(tabla: &Vec<ListaEnlazada>) {
    for i in 0..tabla.len() {
        print!("{}: ", i);

        for par in tabla[i].iter() {
            print!("({},{}) -> ", par.0, par.1);
        }

        println!("None");
    }
}