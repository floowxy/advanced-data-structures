mod lista_enlazada;
mod tabla_hash;

use tabla_hash::{crear, insertar, buscar, eliminar, mostrar};

fn main() {
    let mut tabla = crear(10);

    insertar(&mut tabla, 12, 100);
    insertar(&mut tabla, 22, 200);
    insertar(&mut tabla, 32, 300);
    insertar(&mut tabla, 15, 400);

    mostrar(&tabla);

    println!("{:?}", buscar(&tabla, 22));

    eliminar(&mut tabla, 22);

    mostrar(&tabla);
}