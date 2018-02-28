-- rvu.lua

-- Find a list of views
views = get_views_list()

-- Try to find the given view... 
-- default to the first view in model if no view name is given
view_name = argv[1] or views[1]

-- Ensure that the view exist
if not is_view(view_name) then
    raise("View "..view_name.." does not exist")
end

-- Review
review(view_name)
