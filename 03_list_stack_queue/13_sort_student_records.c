#include "utils.h"
#include "list.h"

#define MAX_SECURITY_NUM  1000
#define BUCKET_NUM        10
#define PASS_NUM          3

int generate_student_info(struct student **info, int num);
void print_student_info(struct student *info, int num);
int radix_sort_student_info(struct student *info, int num);
int radix_sort(struct list *buckets[BUCKET_NUM], int pass_num);
int get_student_info_from_buckets(struct list *buck[BUCKET_NUM], struct student *info, int num);
void clear_buckets(struct list *buck[BUCKET_NUM]);

int main()
{
    int result = SUCCESS;
    int student_num = 0;
    struct student *student_info = NULL;
    struct list *head = NULL;

    printf("Enter student num: ");
    scanf("%d", &student_num);

    result = generate_student_info(&student_info, student_num);
    if (SUCCESS != result)
    {
        print_error("failed to generate students' info!");
        return 0;
    }

    printf("\nbefore radix sorting, the students' info is: \n");
    print_student_info(student_info, student_num);

    result = radix_sort_student_info(student_info, student_num);
    if (SUCCESS != result)
    {
        print_error("failed to sort students' information using radix-sort!");
        return 0;
    }

    printf("\nafter radix sorting, the students' info is: \n");
    print_student_info(student_info, student_num);

    free(student_info);

    return 0;
}

int generate_student_info(struct student **info, int num)
{
    struct student *stud_info = NULL;
    int pos = 0;

    srand((unsigned)time(NULL));

    stud_info = (struct student *)malloc(sizeof(struct student) * num);
    if (NULL == stud_info)
    {
        print_error("failed to malloc memory for student info!");
        return MALLOC_FAIL;
    }

    for (pos = 0; pos < num; pos++)
    {
        stud_info[pos].id = pos + 1;
        stud_info[pos].secu_num = rand() % MAX_SECURITY_NUM;
    }

    *info = stud_info;
    
    return SUCCESS;
}

void print_student_info(struct student *info, int num)
{
    int pos = 0;

    for (pos = 0; pos < num; pos++)
    {
        printf("(%d, %d) ", info[pos].id, info[pos].secu_num);

        if (pos % 5 == 4)
        {
            printf("\n");
        }
    }
}

int radix_sort_student_info(struct student *info, int num)
{
    struct list *buckets[BUCKET_NUM];
    struct list *head = NULL;
    struct list *cur = NULL;
    int result = SUCCESS;

    memset(buckets, 0, sizeof(struct list *) * BUCKET_NUM);

    result = list_create_from_student_arr(&head, info, num);
    if (SUCCESS != result)
    {
        print_error("failed to create list from student array!");
        return result;
    }

    buckets[0] = head->next;  /* discard list's header */
    head->next = NULL;
    list_clear(head);

    result = radix_sort(buckets, PASS_NUM);
    if (SUCCESS != result)
    {
        print_error("failed to radix sort the buckets!");
        clear_buckets(buckets);
        return result;
    }

    result = get_student_info_from_buckets(buckets, info, num);
    if (SUCCESS != result)
    {
        print_error("failed to get student info from buckets!");
        clear_buckets(buckets);
        return result;
    }

    clear_buckets(buckets);

    return SUCCESS;
}

int radix_sort(struct list *buckets[BUCKET_NUM], int pass_num)
{
    int base = 1;
    int pass_id = 0;
    int bucket_id = 0;
    int target_id = 0;
    struct list *sorted[BUCKET_NUM];
    struct list *sorted_last[BUCKET_NUM]; /* record the last node in each list of sorted */
    struct list *cur_bucket = NULL;

    for (pass_id = 0; pass_id < pass_num; pass_id++)
    {
        memset(sorted, 0, sizeof(struct list *) * BUCKET_NUM);
        memset(sorted_last, 0, sizeof(struct list *) * BUCKET_NUM);

        for (bucket_id = 0; bucket_id < BUCKET_NUM; bucket_id++)
        {
            cur_bucket = buckets[bucket_id];

            while (NULL != cur_bucket)
            {
                target_id = ((struct student *)cur_bucket->data)->secu_num / base % BUCKET_NUM;
                buckets[bucket_id] = cur_bucket->next;  /* delete cur_bucket node */
                cur_bucket->next = NULL;

                /* insert cur_bucket to the end of sorted */
                if (NULL == sorted_last[target_id]) 
                {
                    sorted[target_id] = cur_bucket;
                }
                else
                {
                    sorted_last[target_id]->next = cur_bucket;
                }

                sorted_last[target_id] = cur_bucket;
                cur_bucket = buckets[bucket_id];
            }
        }

        memcpy(buckets, sorted, sizeof(struct list *) * BUCKET_NUM);

        base *= 10;
    }

    return SUCCESS;
}

int get_student_info_from_buckets(struct list *buck[BUCKET_NUM], struct student *info, int num)
{
    int pos = 0;
    int id = 0;
    struct list *cur = NULL;

    memset(info, 0, sizeof(struct student) * num);

    for (id = 0; id < BUCKET_NUM; id++)
    {
        cur = buck[id];

        while ((NULL != cur) && (pos < num))
        {
            info[pos].id = ((struct student *)cur->data)->id;
            info[pos].secu_num = ((struct student *)cur->data)->secu_num;

            pos++;
            cur = cur->next;
        }
    }
}

void clear_buckets(struct list *buck[BUCKET_NUM])
{
    int pos = 0;
    struct list *cur = NULL;

    for (pos = 0; pos < BUCKET_NUM; pos++)
    {
        cur = buck[pos];

        while (NULL != cur)
        {
            buck[pos] = cur->next;

            free(cur->data);
            free(cur);

            cur = buck[pos];
        }
    }
}
