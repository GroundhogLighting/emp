-- We tell Emp that we will not make calculations
auto_solve = false 

-- capture the first argument
name = argv[1] --or "Jim"

if name == nil then
    raise "aaa"
end

-- Greet
print("Hello",name)