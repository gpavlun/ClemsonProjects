import datetime
def current_day(curr_date):
    y=curr_date.strftime('%A')
    return y
def next_birthday(cur_birthday):
    nxt=datetime.datetime(datetime.date.today().year,cur_birthday.month,cur_birthday.day)
    if nxt>datetime.datetime.today():    
        t=nxt-datetime.datetime.today()
        a=datetime.date.today().year-cur_birthday.year-1
    else:
        t=datetime.datetime(nxt.year+1,cur_birthday.month,cur_birthday.day)-datetime.datetime.today()
        a=datetime.date.today().year-cur_birthday.year
    s=t.seconds
    d=t.days
    h,c=divmod(s,3600)
    m,s=divmod(c,60)
    print('your age is',a,'and your next birthday is in',d,'day(s)',h,'hours',m,'minutes',s,'seconds')
    




def test_current_day(curr_date):
    print('the day is:')
    x=current_day(curr_date)
    print(x)
def test_next_birthday(cur_birthday):
    next_birthday(cur_birthday)
if __name__ == '__main__':
    test_current_day(datetime.date(int(input('year:')),int(input('month:')),int(input('day:'))))
    test_next_birthday(datetime.date(int(input('year:')),int(input('month:')),int(input('day:'))))
