# импорт библиотек
from tkinter import *
from tkinter.ttk import Combobox

# создание основного окна
window = Tk()
window.geometry('500x350')
window.resizable(0, 0)

# заголовок программы
window.title("Вычисление дня недели по дате")

# текст в окне программы
text_1 = "Выберите дату"
lbl = Label(window, text=text_1)
#lbl.grid(column=0, row=0)
lbl.place(x=90, y=5)

# создание поля для выбора дня
day_list = [x for x in range(1, 32)]
day = Combobox(window, values=day_list, width=3)
day.current(14)
day.place(x=40, y=50)

# создание поля для выбора месяца
month_list = ['Январь', 'Февраль', 'Март',
			  'Апрель', 'Май', 'Июнь',
			  'Июль', 'Август', 'Сентябрь',
			  'Октябрь', 'Ноябрь', 'Декабрь']
month = Combobox(window, values=month_list, state="readonly", width=10)
month.current(6)
month.place(x=110, y=50)

# создание поля для ввода года
year_list = [x for x in range(2010, 2031)]
#year = Combobox(window, values=year_list, width=7)
#year.place(x=250, y=50)
#year.current(0)

default = StringVar(window, value=1410)
year = Entry(window, textvariable=default, width=7)
year.place(x=250, y=47)

window.mainloop()


def weekday(year: int, month: int, day: int) -> int:
	if month < 3:
		year -= 1
		month += 10
	else:
		month -= 2
	return (day + 31 * month // 12 + year + year // 4 - year // 100 + year // 400) % 7

# print(weekday(1991, 12, 10))
