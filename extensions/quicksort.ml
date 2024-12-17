(* this file implements a basic quicksort function
Sumira Naroola and Derek Hessinger

to run: 
ocamlc -o quicksort quicksort.ml
./quicksort
 *)


let rec quicksort cmp = function
  | [] -> []
  | pivot :: rest ->
      let left = List.filter (fun x -> cmp x pivot < 0) rest in
      let right = List.filter (fun x -> cmp x pivot >= 0) rest in
      (quicksort cmp left) @ [pivot] @ (quicksort cmp right)

(* these are the comparison functions *)
let ascending x y = compare x y
let descending x y = compare y x

(* tests *)
let () =
  (* ints, ascending *)
  let int_list = [3; 1; 4; 1; 5; 9; 2; 6; 5; 3; 5] in
  let sorted_ints_asc = quicksort ascending int_list in
  Printf.printf "Integers ascending: %s\n"
    (String.concat ", " (List.map string_of_int sorted_ints_asc));

  (* ints, decending *)
  let sorted_ints_desc = quicksort descending int_list in
  Printf.printf "Integers descending: %s\n"
    (String.concat ", " (List.map string_of_int sorted_ints_desc));

  (* floats, ascending *)
  let float_list = [3.1; 2.5; 1.4; 5.9; 2.2] in
  let sorted_floats_asc = quicksort ascending float_list in
  Printf.printf "Floats ascending: %s\n"
    (String.concat ", " (List.map string_of_float sorted_floats_asc));

  (* strings, alphabetical *)
  let string_list = ["apple"; "banana"; "grape"; "cherry"; "fig"] in
  let sorted_strings_asc = quicksort ascending string_list in
  Printf.printf "Strings ascending: %s\n"
    (String.concat ", " sorted_strings_asc);