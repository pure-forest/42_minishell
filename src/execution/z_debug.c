/// DEBUGGGGG DELETE!!!!!!!!!!!


//printf("Before unset_env:\n");
//print_list(data->export);

void print_list(t_env_nodes *head)
{
    t_env_nodes *curr = head;
    while (curr)
    {
        printf("Node at %p | Name: %s | Next: %p | Prev: %p\n",
               (void *)curr, curr->var_name, (void *)curr->base.next, (void *)curr->base.prev);
        curr = (t_env_nodes *)curr->base.next;
    }
}