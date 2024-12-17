(* parametric polymorphic linked list in ocaml 

Sumira Naroola and Derek Hessinger

to run: 
ocamlc -o linkedlist linkedlist.ml
./linkedlist

In C, you need to use pointers and void * to make a generic linked list, which lets it hold any type of data, but you also have to manually 
manage memory, including freeing it to prevent memory leaks. In OCaml, polymorphism (using type variables like 'a) makes it easy to create a 
generic linked list without needing pointers, and OCaml's garbage collector automatically handles memory, so you don't need to manually free 
anything. This means that OCaml's linked list is simpler to implement and safer, as you don’t risk memory leaks.

 *)


type 'a node =
  | Empty
  | Node of 'a * 'a node ref

type 'a linked_list = {
  head : 'a node ref;
}

(* creates new empty list *)
let ll_create () = { head = ref Empty }

(* adds element to front of the list *)
let ll_push l data =
  l.head := Node (data, ref !(l.head))

(* removes first element and returns its val *)
let ll_pop l =
  match !(l.head) with
  | Empty -> None
  | Node (data, next) ->
      l.head := !next;
      Some data

(* adds element to end of list *)
let ll_append l data =
  let rec aux node =
    match !node with
    | Empty -> node := Node (data, ref Empty)
    | Node (_, next) -> aux next
  in
  aux l.head

(* finds specific element  *)
let ll_find l target compfunc =
  let rec aux = function
    | Empty -> None
    | Node (data, next) ->
        if compfunc data target = 0 then Some data
        else aux !next
  in
  aux !(l.head)

(* remove first matching element  *)
let ll_remove l target compfunc =
  let rec aux prev = function
    | Empty -> None
    | Node (data, next) ->
        if compfunc data target = 0 then (
          prev := !next;
          Some data
        ) else aux prev !next  
  in
  aux l.head !(l.head)

(* counts elements in list *)
let ll_size l =
  let rec aux count = function
    | Empty -> count
    | Node (_, next) -> aux (count + 1) !next
  in
  aux 0 !(l.head)

(* clears list *)
let ll_clear l =
  l.head := Empty

(* can apply a func to every element in the list  *)
let ll_map l mapfunc =
  let rec aux = function
    | Empty -> ()
    | Node (data, next) ->
        mapfunc data;
        aux !next
  in
  aux !(l.head)

(* tests *)
let () =
  let int_list = ll_create () in
  ll_push int_list 1;
  ll_push int_list 2;
  ll_append int_list 3;
  Printf.printf "size of int list: %d\n" (ll_size int_list);
  ll_map int_list (Printf.printf "%d ");
  print_endline "";

  let string_list = ll_create () in
  ll_push string_list "one";
  ll_push string_list "two";
  ll_append string_list "three";
  Printf.printf "size of string list: %d\n" (ll_size string_list);
  ll_map string_list (Printf.printf "%s ");
  print_endline "";