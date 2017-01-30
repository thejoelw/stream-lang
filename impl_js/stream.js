let call_cbs = function(cbs) {
    cbs.forEach(function(cb) {
        cb();
    });
}

let call_cbs_arg = function(cbs, arg) {
    cbs.forEach(function() {
        cb(arg);
    });
}


let Stream = function() {
    let arr = [];
    let opens = 1;

    let add_cbs = [];
    let close_cbs = [];

    this.open = function() {
        opens++;
    };
    this.close = function() {
        opens--;
        if (opens === 0) {
            close_cbs.forEach(function(cb) {
                cb();
            });
        }
    };

    this.on_add = function(cb) {
        // Cannot use forEach because cb could add elements, which forEach won't pick up
        for (let i = 0; i < arr.length; i++) {
            cb(arr[i]);
        }

        add_cbs.push(cb);
    };

    this.on_close = function(cb) {
        close_cbs.push(cb);
    };

    this.add = function(el) {
        arr.push(el);

        for (let i = 0; i < add_cbs.length; i++) {
            add_cbs[i](el);
        }
    };
};


// {+abc = 123} {.abc = 456}
// {+abc = (456, 123)}
//
let first = function() {

};

/*
A function is a stream of assignments
    - No, doesn't really work for functions with side effects.
    - Also, what happens when the resulting stream is filtered?

factorial = {
    -num|Int = in
    <= num ?= 0 -> 1
    <= num ?> 1 -> num * factorial dec num
}

Map and reduce functions.
(range 10) should simply bind the arguments, not execute the function.
    + Then, we can do this: (range 10 -> Stream.sum), which sends a function returning a stream to the Stream.sum reducer.

-> mapping_function
>> aggregation_function

stream >> {
    +count ?= 0
    <= .count = count + 1
}

// .prop updates the first public prop in compositions to the left


Stop program at random points. Optimize code around current program counter.
For example, if multiple stops include (factorial 40) in the call stack, add short-circuit for that function.
Try to prove that (factorial 40 ?= x), and if successful, add shortcut for (factorial 40 -->> x).
*/


let bind = function(el_1, el_2) {
    if (el_2.hasOwnProperty('unbound')) {

    }
};

let compose = function(a, b) {
    let res = new Stream();
    res.open();
    a.on_close(res.close);
    res.open();
    b.on_close(res.close);

    left.on_add(function(el_1) {
        right.on_add(function(el_2) {
            bind(el_1, el_2);
            bind(el_2, el_1);
        });
    });

    return res;
};
