# импорт библиотек
from tkinter import *
from tkinter.ttk import Combobox
from tkinter import messagebox


# основные функции

# алгоритм для подсчета дня недели по дате
def weekday(y: int, m: int, d: int) -> int:
	if m < 3:
		y -= 1
		m += 10
	else:
		m -= 2
	dotw = (d + 31 * m // 12 + y + y // 4 - y // 100 + y // 400) % 7
	dotw_dict = {0: 'Воскресенье', 1: 'Понедельник', 2: 'Вторник', 
				 3: 'Среда', 4: 'Четверг', 5: 'Пятница', 6: 'Суббота'}
	return dotw_dict[dotw]


# вывод дня недели
def clicked():
	try:
		month_value = month.get()
		month_value = month_dict[f"{month_value}"]
		day_value = int(day.get())
		# проверка правильности введенного дня
		if (day_value < 1 or day_value > 31):
			message_1 = "Выберите существующий день"
			messagebox.showinfo('Ошибка', message_1)
			return
		year_value = int(year.get())
		if year_value < 1582:
			message_2 = 'Выберите дату не раньше 15.10.1582. \
						 Именно в тот день был введен григорианский календарь'
			messagebox.showinfo('Ошибка', message_2)
			return		
		year_value = int(year.get())
		# проверка на февраль и високосность
		if year_value % 400 == 0:
			bissextile = True
		elif year_value % 100 == 0:
			bissextile = False
		elif year_value % 4 == 0:
			bissextile = True
		else:
			bissextile = False
		if (month_value == 2 and bissextile == False and day_value > 28):
			messagebox.showinfo('Ошибка', 'В феврале 28 дней')
			return
	except:
		messagebox.showinfo('Ошибка', 'Введите дату')
		return
	messagebox.showinfo('День недели', weekday(year_value, month_value, day_value))


# создание основного окна
window = Tk()
window.geometry('350x150')
window.resizable(0, 0)

# заголовок программы
window.title("Вычисление дня недели по дате")

# текст в окне программы
text_1 = "Выберите дату"
lbl_1 = Label(window, text=text_1)
lbl_1.place(x=115, y=5)
#text_2 = "Этот год \nвисокосный"
#lbl_2 = Label(window, text=text_2)
#lbl_2.place(x=250, y=5)

# создание поля для выбора дня
day_list = [x for x in range(1, 32)]
day = Combobox(window, values=day_list, width=3)
day.current(14)
day.place(x=40, y=50)

# создание поля для выбора месяца
month_dict = {'Январь': 1, 'Февраль': 2, 'Март': 3,
			  'Апрель': 4, 'Май': 5, 'Июнь': 6,
			  'Июль': 7, 'Август': 8, 'Сентябрь': 9,
			  'Октябрь': 10, 'Ноябрь': 11, 'Декабрь': 12}
month = Combobox(window, values=list(month_dict.keys()), state="readonly", width=10)
month.current(9)
month.place(x=110, y=50)

# создание поля для ввода года
#default = StringVar(window, value=1582)
#year = Entry(window, textvariable=default, width=7)
year = Spinbox(window, from_=1582, to=2100, width=7, bg='gray')
year.place(x=250, y=50)

# Кнопка запуска алгоритма
btn = Button(window, text='Узнать', command=clicked, width=10)
btn.grid(column=1, row=0)
btn.place(x=105, y=100)

year_value = int(year.get())
if year_value == 1583:
	text_2 = "Этот год \nвисокосный"
	lbl_2 = Label(window, text=text_2)
	lbl_2.place(x=250, y=5)

window.mainloop()
